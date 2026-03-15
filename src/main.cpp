#include <cmath>
#include <iostream>

#include "Camera.h"
#include "Material.h"
#include "Ray.h"
#include "Vec3.h"

constexpr auto g_ASPECT_RATIO{16.0 / 9.0};
static int g_WIDTH{400};
constexpr auto g_SAMPLES_PER_PIXEL{100};
constexpr auto g_MAX_DEPTH{50};
constexpr auto g_VFOV{20};
const auto g_LOOK_FROM{Vec3(13, 2, 3)};
const auto g_LOOK_AT{Vec3()};
const auto g_VEC_UP{Vec3(0, 1, 0)};
constexpr auto g_DEFOCUS_ANGLE{0.6};
constexpr auto g_FOCUS_DIST{10.0};

const auto material_ground{std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5))};
const auto material_1{std::make_shared<Dielectric>(1.5)};
const auto material_2{std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1))};
const auto material_3{std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0)};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr
            << "USAGE: ./rt.out <IMAGE_WIDTH> <NUMBER_SPHERES> > <IMAGE_LOCATION.ppm>\n";
        return EXIT_FAILURE;
    }

    g_WIDTH = (std::stoi(argv[1]) > 400) ? std::stoi(argv[1]) : g_WIDTH;
    int num_spheres{(std::stoi(argv[2]) < 0) ? 2 : 11};

    // world
    HittableList world(
        {std::make_shared<Sphere>(Vec3(0.0, -1000.0, 0.0), 1000, material_ground),
         std::make_shared<Sphere>(Vec3(0.0, 1.0, 0.0), 1.0, material_1),
         std::make_shared<Sphere>(Vec3(-4.0, 1.0, 0.0), 1.0, material_2),
         std::make_shared<Sphere>(Vec3(4.0, 1.0, 0.0), 1.0, material_3)});

    for (int i{-11}; i < num_spheres; ++i) {
        for (int j{-11}; j < num_spheres; ++j) {
            auto choose_mat{gen_random_double()};
            Vec3 center(i + 0.9 * gen_random_double(), 0.2,
                        j + 0.9 * gen_random_double());

            if (((center - Vec3(4.0, 0.2, 0.0)).length() > 0.9)) {
                std::shared_ptr<Material> mat{};
                auto r{gen_random_double(0.2, 0.5)};

                if (choose_mat < 0.8) {
                    auto albedo = Color::gen_random() * Color::gen_random();
                    mat = std::make_shared<Lambertian>(albedo);
                    world.push_back(std::make_shared<Sphere>(center, r, mat));
                } else if (choose_mat < 0.95) {
                    auto albedo{Color::gen_random(0.5, 1.0)};
                    auto fuzz{gen_random_double(0, 0.5)};
                    mat = std::make_shared<Metal>(albedo, fuzz);
                    world.push_back(std::make_shared<Sphere>(center, r, mat));
                } else {
                    mat = std::make_shared<Dielectric>(1.5);
                    world.push_back(std::make_shared<Sphere>(center, r, mat));
                }
            }
        }
    }

    // camera
    Camera camera(g_ASPECT_RATIO, g_WIDTH, g_SAMPLES_PER_PIXEL, g_MAX_DEPTH, g_VFOV,
                  g_LOOK_FROM, g_LOOK_AT, g_VEC_UP, g_DEFOCUS_ANGLE, g_FOCUS_DIST);
    camera.render(world);
}