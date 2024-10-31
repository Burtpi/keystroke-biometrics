#ifndef SWARM_H_
#define SWARM_H_

#include <optimizer/particle.h>

#include <vector>

namespace optimizer {
class Swarm {
   public:
    Swarm();
    void Optimize();

   private:
    int number_of_particles_;
    int max_iterations_;
    float inertia_;
    float cognitive_;
    float social_;
    std::vector<Particle> particles_;
    float CalculateFAR();
    float CalculateFRR();
    float CalcuilateEER();
    void UpdateParticleVelocities();
    void FindGlobalBest();
};
}  // namespace optimizer

#endif