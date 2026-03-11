#include "Camera.h"
#include "Color.h"
#include "Interval.h"
#include "Util.h"

Camera::Camera() : Camera(1.0, 100) {}

Camera::Camera(double aspect_ratio, int img_w)
    : m_aspect_ratio{aspect_ratio}, m_img_w{img_w}, m_img_h{}, m_center{},
      m_pixel00_loc{}, m_pixel_delta_u{}, m_pixel_delta_v{} {
    initialise();
}

void Camera::render(const Hittable& world) {
    std::cout << "P3\n" << m_img_w << ' ' << m_img_h << "\n255\n";

    for (int j{}; j < m_img_h; ++j) {
        std::clog << "\rScanlines remaining: " << (m_img_h - j) << ' ' << std::flush;
        for (int i{}; i < m_img_w; ++i) {
            auto pixel_center{m_pixel00_loc + (i * m_pixel_delta_u) +
                              (j * m_pixel_delta_v)};
            auto ray_direction{pixel_center - m_center};
            Ray r(m_center, ray_direction);
            auto pixel_color{ray_color(r, world)};

            write_color(pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
}

void Camera::initialise() {
    m_img_h = static_cast<int>(m_img_w / m_aspect_ratio);
    m_img_h = (m_img_h < 1) ? 1 : m_img_h;

    auto focal_length{1.0};
    auto viewport_h{2.0};
    auto viewport_w{viewport_h * (static_cast<double>(m_img_w) / m_img_h)};

    Vec3 viewport_u(viewport_w, 0, 0);
    Vec3 viewport_v(0, -viewport_h, 0);

    m_pixel_delta_u = viewport_u / m_img_w;
    m_pixel_delta_v = viewport_v / m_img_h;

    auto viewport_upper_left{m_center - Vec3(0, 0, focal_length) - viewport_u / 2 -
                             viewport_v / 2};
    m_pixel00_loc = viewport_upper_left + 0.5 * (m_pixel_delta_u + m_pixel_delta_v);
}

Color Camera::ray_color(const Ray& r, const Hittable& world) const {
    HitRecord rec{};
    if (world.hit(r, Interval(0, infinity), rec))
        return 0.5 * (rec.m_normal + Color(1, 1, 1));

    auto unit_direction{unit_vector(r.direction())};
    auto a{0.5 * (unit_direction.y() + 1.0)};
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}