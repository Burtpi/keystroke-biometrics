#ifndef UTILS_MATH_
#define UTILS_MATH_

#include <vector>
namespace utils::math {
template <typename T>
double CalculateMean(const std::vector<T> &values);
template <typename T>
double CalculateStandardDeviation(const std::vector<T> &values);
double CalculateZScore(double value, double mean, double std_deviation);
}  // namespace utils::math
#endif