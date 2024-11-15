#ifndef STATISTICS_H_
#define STATISTICS_H_

namespace database::models {
struct Statistics {
    // -----------------------------------------------------------
    // Struct for storing calculated data of descriptors
    // -----------------------------------------------------------
    double mean;
    double std_deviation;
};
}  // namespace database::models

#endif