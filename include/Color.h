#pragma once

#include <iostream>

#include "Vec3.h"
#include "Interval.h"

using Color = Vec3;

inline void write_color(const Color& pixel_color) {
    auto r{pixel_color.x()};
    auto g{pixel_color.y()};
    auto b{pixel_color.z()};

    static const Interval intensity(0.000, 0.999);
    auto rbyte{256 * intensity.clamp(r)};
    auto gbyte{256 * intensity.clamp(g)};
    auto bbyte{256 * intensity.clamp(b)};

    std::cout << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}