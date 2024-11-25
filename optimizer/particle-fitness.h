#ifndef PARTICLE_FITNESS_H_
#define PARTICLE_FITNESS_H_

namespace optimizer {
struct ParticleFitness {
    // -----------------------------------------------------------
    // Struct for storing fitness data for a Particle
    // -----------------------------------------------------------
    float fitness;
    float best_fitness;
    float fitness_threshold;
    float best_fitness_threshold;
};
}  // namespace optimizer

#endif