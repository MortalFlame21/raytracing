#pragma once

#include <chrono>
#include <limits>
#include <numbers>
#include <random>

const double infinity{std::numeric_limits<double>::infinity()};

inline double degrees_to_radians(double degrees) {
    return degrees * std::numbers::pi / 180;
}

inline std::mt19937 generate_seed() {
    std::random_device rd{};
    std::seed_seq seed_seq{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
    return std::mt19937{seed_seq};
}

inline std::mt19937 mt{generate_seed()};

// min <= n < max
inline double gen_random_double(double min, double max) {
    return std::uniform_real_distribution{min, max}(mt);
}

// 0.0 <= n < 1.0
inline double gen_random_double() { return gen_random_double(0.0, 1.0); }
