#include <utils/math/utils-math.h>

double utils::math::CalculateZScore(double value, double mean,
                                    double std_deviation) {
    return (value - mean) / std_deviation;
}