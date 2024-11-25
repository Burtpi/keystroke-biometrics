#include <fmt/ranges.h>
#include <optimizer/swarm.h>
#include <utils/calc/utils-calc.h>

optimizer::Swarm::Swarm() {
    number_of_particles_ = 50;
    max_iterations_ = 1000;
    inertia_ = 0.7;
    cognitive_ = 1.5;
    social_ = 1.5;
    particles_ = std::vector<Particle>(number_of_particles_, Particle());
    global_best_weights_ = {1, 1, 1, 1};
    global_best_fitness_ = std::numeric_limits<float>::max();
    num_generator_ = std::mt19937(std::random_device{}());
    u_r_distrib_ = std::uniform_real_distribution<float>(0, 1);
}

void optimizer::Swarm::Optimize(
    std::vector<database::templates::TemplateContainer>& template_containers,
    std::vector<database::containers::MergedObjectsContainer>&
        merged_objects_containers) {
    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Running optimizer.");

    for (Particle& p : particles_) {
        p.Initialize();
    }

    for (int iteration = 0; iteration < max_iterations_; iteration++) {
        for (Particle& particle : particles_) {
            std::vector<std::vector<bool>> is_genuine_overall;
            std::vector<std::vector<double>> scores_overall;

            // For each of the data sets, calculate scores for all templates
            for (database::containers::MergedObjectsContainer merged_objects :
                 merged_objects_containers) {
                std::vector<bool> is_genuine;
                std::vector<double> scores;
                for (database::templates::TemplateContainer template_container :
                     template_containers) {
                    database::containers::MergedObjectsContainer
                        merged_objects_copy = merged_objects;
                    utils::calc::CalculateCurrentObjects(particle.GetWeights(),
                                                         merged_objects_copy,
                                                         template_container);

                    // Save scores and information about genuity of verification
                    for (database::models::CalcTemplate& calc_template :
                         template_container.GetCalcTemplate()) {
                        // Get scores only for the templates that match language
                        // with the data set
                        if (calc_template.language.compare(
                                merged_objects.GetLanguage()) == 0) {
                            is_genuine.emplace_back(
                                merged_objects.GetName() ==
                                template_container.GetName());
                            scores.emplace_back(calc_template.score);
                        }
                    }
                }
                is_genuine_overall.emplace_back(is_genuine);
                scores_overall.emplace_back(scores);
            }
            // Get current position for particle
            particle.SetFitness(
                CalculateEER(is_genuine_overall, scores_overall));

            particle.UpdateBestPosition();
        }
        FindGlobalBestWeights(particles_);
        UpdateParticleVelocities(particles_);

        global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
            "Iteration " + std::to_string(iteration) +
            " - Best EER: " + std::to_string(global_best_fitness_) + " with " +
            std::to_string(global_best_fitness_threshold_) + " threshold.");
        global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
            "Current global best weights: {}",
            fmt::join(global_best_weights_, " "));
    }
    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Successfully optimized the weights for descriptors.");
}

std::pair<float, float> optimizer::Swarm::CalculateEER(
    const std::vector<std::vector<bool>>& is_genuine,
    const std::vector<std::vector<double>>& scores) {
    float best_threshold = 0;
    float min_diff = std::numeric_limits<float>::max();
    float eer = 0;
    float far1;
    float frr1;

    for (float threshold = 0; threshold <= 100; threshold += 0.001) {
        float false_acc_rate = CalculateFAR(is_genuine, scores, threshold);
        float false_rej_rate = CalculateFRR(is_genuine, scores, threshold);
        float diff = abs(false_acc_rate - false_rej_rate);

        if (diff < min_diff) {
            min_diff = diff;
            best_threshold = threshold;
            // Approximate EER
            eer = (false_acc_rate + false_rej_rate) / 2;
            far1 = false_acc_rate;
            frr1 = false_rej_rate;
        }
    }
    std::ostringstream oss;
    return std::make_pair(eer, best_threshold);
}

float optimizer::Swarm::CalculateFAR(
    const std::vector<std::vector<bool>>& is_genuine,
    const std::vector<std::vector<double>>& scores, float threshold) {
    // Calculate how many data sets were falsely accepted
    int false_accepts = 0;
    int impostors = 0;

    for (int i = 0; i < scores.size(); i++) {
        for (int j = 0; j < scores[i].size(); j++) {
            if (!is_genuine[i][j]) {
                impostors++;
                if (scores[i][j] >= threshold) {
                    false_accepts++;
                }
            }
        }
    }
    return (impostors == 0) ? 0 : static_cast<float>(false_accepts) / impostors;
}

float optimizer::Swarm::CalculateFRR(
    const std::vector<std::vector<bool>>& is_genuine,
    const std::vector<std::vector<double>>& scores, float threshold) {
    // Calculate how many data sets were falsely rejected
    int false_rejects = 0;
    int genuine = 0;

    for (int i = 0; i < scores.size(); i++) {
        for (int j = 0; j < scores[i].size(); j++) {
            if (is_genuine[i][j]) {
                genuine++;
                if (scores[i][j] < threshold) {
                    false_rejects++;
                }
            }
        }
    }
    return (genuine == 0) ? 0 : static_cast<float>(false_rejects) / genuine;
}

void optimizer::Swarm::FindGlobalBestWeights(
    const std::vector<Particle>& particles) {
    for (Particle particle : particles) {
        if (particle.GetBestFitness() < global_best_fitness_) {
            global_best_fitness_ = particle.GetBestFitness();
            global_best_weights_ = particle.GetBestWeights();
            global_best_fitness_threshold_ = particle.GetBestFitnessThreshold();
        }
    }
}

void optimizer::Swarm::UpdateParticleVelocities(
    std::vector<Particle>& particles) {
    for (Particle& particle : particles) {
        for (size_t i = 0; i < particle.GetWeights().size(); i++) {
            float r1 = u_r_distrib_(num_generator_);
            float r2 = u_r_distrib_(num_generator_);

            // Particle velocity formula where:
            //  inertia - controls momentum of the particle
            //  cognitive - balances individual influence
            //  social - balances group influence
            //  r1, r2 - random values in the range [0, 1]
            particle.GetVelocity()[i] =
                inertia_ * particle.GetVelocity()[i] +
                cognitive_ * r1 *
                    (particle.GetBestWeights()[i] - particle.GetWeights()[i]) +
                social_ * r2 *
                    (global_best_weights_[i] - particle.GetWeights()[i]);

            // Clamp the particle's velocity to the range [-2.0, 2.0] to prevent
            // overshooting
            particle.GetVelocity()[i] =
                std::max(-2.0f, std::min(particle.GetVelocity()[i], 2.0f));

            particle.GetWeights()[i] += particle.GetVelocity()[i];
        }
    }
}