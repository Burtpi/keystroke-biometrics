#ifndef UTILS_ERROR_H_
#define UTILS_ERROR_H_

#include <stdexcept>
#include <string>

void GSLErrorHandler(const char* reason, const char* file, int line,
                     int gsl_errno) {
    throw std::runtime_error("GSL Error occured: " + std::string(reason) +
                             " at " + file + ":" + std::to_string(line));
}

void FFTWErrorHandler() {
    throw std::runtime_error("FFTW failed to create plan.");
}

#endif