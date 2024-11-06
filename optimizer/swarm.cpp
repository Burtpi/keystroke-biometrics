#include <optimizer/swarm.h>
#include <utils/calc/utils-calc.h>

optimizer::Swarm::Swarm() {
    number_of_particles_ = 50;
    max_iterations_ = 1000;
    inertia_ = 0.7;
    cognitive_ = 1.5;
    social_ = 1.5;
    particles_ = std::vector<Particle>(number_of_particles_, Particle());
    global_best_weights = {1, 1, 1, 1};
    global_best_fitness = std::numeric_limits<float>::max();
    num_generator_ = std::mt19937(std::random_device{}());
    u_r_distrib_ = std::uniform_real_distribution<float>(0, 2);
}

void optimizer::Swarm::Optimize(
    std::vector<database::templates::TemplateContainer>& template_containers,
    std::vector<database::containers::MergedObjectsContainer>&
        merged_objects_containers) {
    for (Particle& p : particles_) {
        p.Initialize();
    }

    for (int iteration = 0; iteration < max_iterations_; iteration++) {
        for (Particle& particle : particles_) {
            std::vector<std::vector<bool>> is_genuine_overall;
            std::vector<std::vector<double>> scores_overall;

            for (database::containers::MergedObjectsContainer merged_objects :
                 merged_objects_containers) {
                std::vector<bool> is_genuine;
                std::vector<double> scores;
                for (database::templates::TemplateContainer template_container :
                     template_containers) {
                    utils::calc::CalculateCurrentObjects(particle.GetWeights(),
                                                         merged_objects,
                                                         template_container);
                    for (database::models::CalcTemplate& calc_template :
                         template_container.GetCalcTemplate()) {
                        is_genuine.emplace_back(merged_objects.GetName() ==
                                                template_container.GetName());
                        scores.emplace_back(calc_template.score);
                    }
                }
                is_genuine_overall.emplace_back(is_genuine);
                scores_overall.emplace_back(scores);
            }

            particle.SetFitness(
                CalculateEER(is_genuine_overall, scores_overall));

            particle.UpdateBestPosition();
        }

        FindGlobalBestWeights(particles_);
        UpdateParticleVelocities(particles_);
    }
}

float optimizer::Swarm::CalculateEER(
    const std::vector<std::vector<bool>>& is_genuine,
    const std::vector<std::vector<double>>& scores) {
    float best_threshold = 0;
    float min_diff = std::numeric_limits<float>::max();
    float eer = 0;

    for (float threshold = 0; threshold <= 100; threshold += 0.1) {
        float false_acc_rate = CalculateFAR(is_genuine, scores, threshold);
        float false_rej_rate = CalculateFRR(is_genuine, scores, threshold);
        float diff = abs(false_acc_rate - false_rej_rate);

        if (diff < min_diff) {
            min_diff = diff;
            best_threshold = threshold;
            eer = (false_acc_rate + false_rej_rate) / 2;
        }
    }
    return eer;
}

float optimizer::Swarm::CalculateFAR(
    const std::vector<std::vector<bool>>& is_genuine,
    const std::vector<std::vector<double>>& scores, float threshold) {
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
        if (particle.GetBestFitness() < global_best_fitness) {
            global_best_fitness = particle.GetBestFitness();
            global_best_weights = particle.GetBestWeights();
        }
    }
}

void optimizer::Swarm::UpdateParticleVelocities(
    std::vector<Particle>& particles) {
    for (Particle& particle : particles) {
        for (size_t i = 0; i < particle.GetWeights().size(); i++) {
            float r1 = u_r_distrib_(num_generator_);
            float r2 = u_r_distrib_(num_generator_);
            particle.GetVelocity()[i] =
                inertia_ * particle.GetVelocity()[i] +
                cognitive_ * r1 *
                    (particle.GetBestWeights()[i] - particle.GetWeights()[i]) +
                social_ * r2 *
                    (global_best_weights[i] - particle.GetWeights()[i]);
            particle.GetVelocity()[i] =
                std::max(-2.0f, std::min(particle.GetVelocity()[i], 2.0f));

            particle.GetWeights()[i] += particle.GetVelocity()[i];
        }
    }
}