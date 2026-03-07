#include <iostream>

#include "Color.h"
#include "Ray.h"
#include "Vec3.h"

bool hit_sphere(const Vec3& center, double radius, const Ray& r) {
    Vec3 oc{center - r.origin()};
    auto a{dot(r.direction(), r.direction())}; // a = d*d
    auto b{-2.0 * dot(r.direction(), oc)};     // b = -2 * (C - Q)
    auto c{dot(oc, oc) - radius * radius};     // c = (C - Q) * (C - Q) - r^2
    auto discriminant{b * b - 4 * a * c};      // b^2 - 4ac
    return discriminant >= 0;                  // 1 or 2 roots
}

Color ray_color(const Ray& r) {
    if (hit_sphere(Vec3(0, 0, -1), 0.5, r))
        return Color(1, 0, 0);
    auto unit_direction{unit_vector(r.direction())};
    auto a{0.5 * (unit_direction.y() + 1.0)};
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main() {
    auto aspect_ratio{16.0 / 9.0};
    auto img_w{400};
    auto img_h{static_cast<int>(img_w / aspect_ratio)};
    img_h = (img_h < 1) ? 1 : img_h;

    auto focal_length{1.0};
    auto viewport_h{2.0};
    auto viewport_w{viewport_h * (static_cast<double>(img_w) / img_h)};
    Vec3 camera_center{};

    Vec3 viewport_u{viewport_w, 0, 0};
    Vec3 viewport_v{0, -viewport_w, 0};

    auto pixel_delta_u{viewport_u / img_w};
    auto pixel_delta_v{viewport_v / img_h};

    auto viewport_upper_left{camera_center - Vec3(0, 0, focal_length) - viewport_u / 2 -
                             viewport_v / 2};
    auto pixel100_loc{viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v)};

    // header
    std::cout << "P3\n" << img_w << ' ' << img_w << "\n255\n";

    for (int j{}; j < img_h; ++j) {
        std::clog << "\rScanlines remaining: " << (img_h - j) << ' ' << std::flush;
        for (int i{}; i < img_w; ++i) {
            auto pixel_center{pixel100_loc + (i * pixel_delta_u) + (j * pixel_delta_v)};
            auto ray_direction{pixel_center - camera_center};
            Ray r{camera_center, ray_direction};
            auto pixel_color{ray_color(r)};

            write_color(pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
}