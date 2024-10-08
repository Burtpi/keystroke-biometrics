#include <utils/math/utils-math.h>

template <typename T>
double utils::math::CalculateMean(const std::vector<T> &values) {
    T sum = 0;
    for (T value : values) {
        sum += value;
    }
    return sum / values.size();
}

template <typename T>
double utils::math::CalculateStandardDeviation(const std::vector<T> &values) {
    double mean = CalculateMean<T>(values);
    double sum = 0.0;

    for (T value : values) {
        double diff = value - mean;
        sum += diff * diff;
    }

    return std::sqrt(sum / values.size());
}

double utils::math::CalculateZScore(double value, double mean,
                                    double std_deviation) {
    return (value - mean) / std_deviation;
}