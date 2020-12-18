#pragma once

#include <cmath>
#include <limits>
#include <random>

const double kInfinity = std::numeric_limits<double>::infinity();
const double kEpsilon = 100*std::numeric_limits<double>::epsilon();

constexpr double PI = 2*acos(0.0);

inline double RandomDouble() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double RandomDouble(double min, double max) {
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double DegreesToRadians(double degrees) {
    return degrees * PI / 180.0;
}
