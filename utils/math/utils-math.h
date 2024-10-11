#ifndef UTILS_MATH_
#define UTILS_MATH_

#include <database/models/statistics.h>

#include <cmath>
#include <vector>
namespace utils::math {
template <typename T>
double CalculateMean(const std::vector<T> &values) {
    T sum = 0;
    for (T value : values) {
        sum += value;
    }
    return sum / values.size();
}
template <typename T>
double CalculateStandardDeviation(const std::vector<T> &values) {
    double mean = CalculateMean<T>(values);
    double sum = 0.0;

    for (T value : values) {
        double diff = value - mean;
        sum += diff * diff;
    }

    return std::sqrt(sum / values.size());
}
double CalculateZScore(double value, double mean, double std_deviation) {
    return (value - mean) / std_deviation;
}

template <typename T>
database::models::Statistics CalculateDescriptor(
    std::vector<T> &descriptor_data) {
    double mean = utils::math::CalculateMean(descriptor_data);
    double std_deviation =
        utils::math::CalculateStandardDeviation(descriptor_data);
    return mean, std_deviation;
}

}  // namespace utils::math
#endif