#ifndef PARTICLE_WEIGHTS_H_
#define PARTICLE_WEIGHTS_H_

#include <vector>

namespace optimizer {
struct ParticleWeights {
    std::vector<float> weights;
    std::vector<float> best_weights;
};
}  // namespace optimizer

#endif