#pragma once

#include <limits>
#include <numbers>

const double infinity{std::numeric_limits<double>::infinity()};

inline double degrees_to_radians(double degrees) {
    return degrees * std::numbers::pi / 180;
}
