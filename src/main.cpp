#include <cmath>
#include <iostream>

#include "Camera.h"
#include "Material.h"
#include "Ray.h"
#include "Vec3.h"

constexpr auto g_ASPECT_RATIO{16.0 / 9.0};
constexpr auto g_WIDTH{400};
constexpr auto g_SAMPLES_PER_PIXEL{100};
constexpr auto g_MAX_DEPTH{50};
constexpr auto g_VFOV{90};
const auto g_LOOK_FROM{Vec3(-2, 2, 1)};
const auto g_LOOK_AT{Vec3(0, 0, -1)};
const auto g_VEC_UP{Vec3(0, 1, 0)};

const auto material_ground{std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0))};
const auto material_center{std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5))};
const auto material_left{std::make_shared<Dielectric>(1.50)};
const auto material_bubble{std::make_shared<Dielectric>(1.00 / 1.50)};
const auto material_right{std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0)};

int main() {
    // world
    HittableList world(
        {std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100, material_ground),
         std::make_shared<Sphere>(Vec3(0.0, 0.0, -1.2), 0.5, material_center),
         std::make_shared<Sphere>(Vec3(-1.0, 0.0, -1.0), 0.5, material_left),
         std::make_shared<Sphere>(Vec3(-1.0, 0.0, -1.0), 0.4, material_bubble),
         std::make_shared<Sphere>(Vec3(1.0, 0.0, -1.0), 0.5, material_right)});

    // camera
    Camera camera(g_ASPECT_RATIO, g_WIDTH, g_SAMPLES_PER_PIXEL, g_MAX_DEPTH, g_VFOV,
                  g_LOOK_FROM, g_LOOK_AT, g_VEC_UP);
    camera.render(world);
}