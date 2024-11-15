#ifndef PARTICLE_FITNESS_H_
#define PARTICLE_FITNESS_H_

namespace optimizer {
struct ParticleFitness {
    // -----------------------------------------------------------
    // Struct for storing calculated data of descriptors
    // -----------------------------------------------------------
    float fitness;
    float best_fitness;
};
}  // namespace optimizer

#endif