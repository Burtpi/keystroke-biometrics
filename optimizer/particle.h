#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <optimizer/particle-fitness.h>
#include <optimizer/particle-weights.h>

#include <vector>

namespace optimizer {
class Particle {
   public:
    Particle();
    void UpdateBestPosition();

   private:
    ParticleWeights particle_weights_;
    ParticleFitness particle_fitness_;
    std::vector<float> particle_velocity_;

    void Initialize();
};
}  // namespace optimizer

#endif