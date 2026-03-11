#include <cmath>
#include <iostream>

#include "Camera.h"
#include "Ray.h"
#include "Vec3.h"

constexpr auto g_ASPECT_RATIO{16.0 / 9.0};
constexpr auto g_WIDTH{400};
constexpr auto g_SAMPLES_PER_PIXEL{100};

int main() {
    // world
    HittableList world({std::make_shared<Sphere>(Vec3(0, 0, -1), 0.5),
                        std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100)});

    // camera
    Camera camera(g_ASPECT_RATIO, g_WIDTH, g_SAMPLES_PER_PIXEL);
    camera.render(world);
}