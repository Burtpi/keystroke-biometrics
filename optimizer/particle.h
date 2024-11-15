#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <optimizer/particle-fitness.h>
#include <optimizer/particle-weights.h>

#include <vector>

namespace optimizer {
class Particle {
    // -----------------------------------------------------------
    // Part of a swarm
    //
    // Used for finding optimal weights for the descriptors
    // -----------------------------------------------------------
   public:
    Particle();
    std::vector<float>& GetWeights();
    std::vector<float>& GetBestWeights();
    std::vector<float>& GetVelocity();
    float& GetBestFitness();
    void SetFitness(float fitness);
    void UpdateBestPosition();
    void Initialize();

   private:
    ParticleWeights particle_weights_;
    ParticleFitness particle_fitness_;
    std::vector<float> particle_velocity_;
};
}  // namespace optimizer

#endif