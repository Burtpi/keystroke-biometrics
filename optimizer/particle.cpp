#include <config/config-manager.h>
#include <optimizer/particle.h>

#include <random>

optimizer::Particle::Particle() {
    particle_weights_.weights = std::vector<float>(4, 0);
    particle_weights_.best_weights = std::vector<float>(4, 0);
    particle_fitness_.fitness = std::numeric_limits<float>::max();
    particle_fitness_.best_fitness = std::numeric_limits<float>::max();
    particle_velocity_ = std::vector<float>(4, 0);
}

std::vector<float>& optimizer::Particle::GetWeights() {
    return particle_weights_.weights;
}

std::vector<float>& optimizer::Particle::GetBestWeights() {
    return particle_weights_.best_weights;
}

std::vector<float>& optimizer::Particle::GetVelocity() {
    return particle_velocity_;
}

float& optimizer::Particle::GetBestFitness() {
    return particle_fitness_.best_fitness;
}

void optimizer::Particle::SetFitness(float fitness) {
    particle_fitness_.fitness = fitness;
}

void optimizer::Particle::Initialize() {
    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Initializing particles.");

    // Assign randomly generated weights for the descriptors
    std::random_device random_device;
    std::mt19937 num_generator(random_device());
    std::uniform_real_distribution<float> u_r_distrib(-5, 5);
    for (float& weight : particle_weights_.weights) {
        weight = u_r_distrib(num_generator);
    }
    particle_weights_.best_weights = particle_weights_.weights;

    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Particles initialized.");
}

void optimizer::Particle::UpdateBestPosition() {
    if (particle_fitness_.fitness < particle_fitness_.best_fitness) {
        particle_weights_.best_weights = particle_weights_.weights;
        particle_fitness_.best_fitness = particle_fitness_.fitness;
    }
}