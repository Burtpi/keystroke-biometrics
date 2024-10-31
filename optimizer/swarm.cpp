#include <optimizer/swarm.h>

optimizer::Swarm::Swarm() {
    number_of_particles_ = 50;
    max_iterations_ = 100;
    inertia_ = 0.7f;
    cognitive_ = 1.5f;
    social_ = 1.5f;
    particles_ = std::vector<Particle>(number_of_particles_, Particle());
}