#pragma once

#include <iostream>

#include "Interval.h"
#include "Vec3.h"

using Color = Vec3;

inline double linear_to_gamma(double linear_component) {
    return (linear_component > 0.0) ? std::sqrt(linear_component) : 0.0;
}

inline void write_color(const Color& pixel_color) {
    auto r{pixel_color.x()};
    auto g{pixel_color.y()};
    auto b{pixel_color.z()};

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const Interval intensity(0.000, 0.999);
    auto rbyte{256 * intensity.clamp(r)};
    auto gbyte{256 * intensity.clamp(g)};
    auto bbyte{256 * intensity.clamp(b)};

    std::cout << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}