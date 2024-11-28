#ifndef SWARM_H_
#define SWARM_H_

#include <database/containers/merged-objects-container.h>
#include <database/templates/template-container.h>
#include <optimizer/particle.h>

#include <random>
#include <vector>

namespace optimizer {
class Swarm {
    // -----------------------------------------------------------
    // Optimizer class based on Particle Swarm Optimization
    //
    // Used as a search space for particles to find the optimal weights
    // for the descriptors, based on minimizing the Equal Error Rate of the
    // given optimization data
    // -----------------------------------------------------------
   public:
    Swarm();
    void Optimize(std::vector<database::templates::TemplateContainer>&
                      template_containers,
                  std::vector<database::containers::MergedObjectsContainer>&
                      merged_objects_containers);

   private:
    int number_of_particles_;
    int max_iterations_;
    float inertia_;
    float cognitive_;
    float social_;
    std::vector<float> global_best_weights_;
    float global_best_fitness_;
    float global_best_fitness_threshold_;
    std::vector<Particle> particles_;
    std::mt19937 num_generator_;
    std::uniform_real_distribution<float> u_r_distrib_;
    static float CalculateFAR(const std::vector<std::vector<bool>>& is_genuine,
                              const std::vector<std::vector<double>>& scores,
                              float threshold);
    static float CalculateFRR(const std::vector<std::vector<bool>>& is_genuine,
                              const std::vector<std::vector<double>>& scores,
                              float threshold);
    static std::pair<float, float> CalculateEER(
        const std::vector<std::vector<bool>>& is_genuine,
        const std::vector<std::vector<double>>& scores);
    void UpdateParticleVelocities(std::vector<Particle>& particles);
    void FindGlobalBestWeights(const std::vector<Particle>& particles);
    static void ProcessParticle(
        Particle& particle,
        std::vector<database::templates::TemplateContainer> template_containers,
        std::vector<database::containers::MergedObjectsContainer>
            merged_objects_containers);
};
}  // namespace optimizer

#endif