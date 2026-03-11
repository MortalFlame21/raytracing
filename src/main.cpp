#include <cmath>
#include <iostream>

#include "Color.h"
#include "Hittable.h"
#include "Ray.h"
#include "Util.h"
#include "Vec3.h"

double hit_sphere(const Vec3& center, double radius, const Ray& r) {
    Vec3 oc{center - r.origin()};
    auto a{r.direction().length_squared()};
    auto h{dot(r.direction(), oc)};
    auto c{oc.length_squared() - radius * radius};
    auto discriminant{h * h - a * c};

    // 1 or 2 roots
    return (discriminant < 0) ? -1.0 : (h - std::sqrt(discriminant)) / a;
}

Color ray_color(const Ray& r, const Hittable& world) {
    HitRecord rec{};
    if (world.hit(r, 0, infinity, rec))
        return 0.5 * (rec.m_normal + Color(1, 1, 1));

    auto unit_direction{unit_vector(r.direction())};
    auto a{0.5 * (unit_direction.y() + 1.0)};
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main() {
    auto aspect_ratio{16.0 / 9.0};
    auto img_w{400};
    auto img_h{static_cast<int>(img_w / aspect_ratio)};
    img_h = (img_h < 1) ? 1 : img_h;

    // world
    HittableList world{};
    world.push_back(std::make_shared<Sphere>(Vec3(0, 0, -1), 0.5));
    world.push_back(std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100));

    // camera
    auto focal_length{1.0};
    auto viewport_h{2.0};
    auto viewport_w{viewport_h * (static_cast<double>(img_w) / img_h)};
    Vec3 camera_center{};

    Vec3 viewport_u(viewport_w, 0, 0);
    Vec3 viewport_v(0, -viewport_h, 0);

    auto pixel_delta_u{viewport_u / img_w};
    auto pixel_delta_v{viewport_v / img_h};

    auto viewport_upper_left{camera_center - Vec3(0, 0, focal_length) - viewport_u / 2 -
                             viewport_v / 2};
    auto pixel00_loc{viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v)};

    // header
    std::cout << "P3\n" << img_w << ' ' << img_h << "\n255\n";

    for (int j{}; j < img_h; ++j) {
        std::clog << "\rScanlines remaining: " << (img_h - j) << ' ' << std::flush;
        for (int i{}; i < img_w; ++i) {
            auto pixel_center{pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v)};
            auto ray_direction{pixel_center - camera_center};
            Ray r(camera_center, ray_direction);
            auto pixel_color{ray_color(r, world)};

            write_color(pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
}