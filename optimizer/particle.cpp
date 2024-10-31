#include <optimizer/particle.h>

#include <random>

optimizer::Particle::Particle() {
    particle_weights_.weights = std::vector<float>(4, 0.0f);
    particle_weights_.best_weights = std::vector<float>(4, 0.0f);
    particle_fitness_.fitness = std::numeric_limits<float>::max();
    particle_fitness_.best_fitness = std::numeric_limits<float>::max();
    particle_velocity_ = std::vector<float>(4, 0.0f);
    Initialize();
}

void optimizer::Particle::Initialize() {
    std::random_device random_device;
    std::mt19937 num_generator(random_device());
    std::uniform_real_distribution<> u_r_distrib(0.0, 2.0);
    for (float& weight : particle_weights_.weights) {
        weight = u_r_distrib(num_generator);
    }
    particle_weights_.best_weights = particle_weights_.weights;
}

void optimizer::Particle::UpdateBestPosition() {
    if (particle_fitness_.fitness < particle_fitness_.best_fitness) {
        particle_weights_.best_weights = particle_weights_.weights;
        particle_fitness_.best_fitness = particle_fitness_.fitness;
    }
}