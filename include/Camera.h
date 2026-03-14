#pragma once

#include "Color.h"
#include "Hittable.h"

class Camera {
public:
    Camera();
    Camera(double aspect_ratio, int img_h, int samples_per_pixel, int max_depth,
           double vertical_fov);
    void render(const Hittable& world);

private:
    double m_aspect_ratio;
    double m_pixel_samples_scale;
    double m_vertical_fov;
    int m_samples_per_pixel;
    int m_img_w;
    int m_img_h;
    int m_max_depth;
    Vec3 m_center;
    Vec3 m_pixel00_loc;
    Vec3 m_pixel_delta_u;
    Vec3 m_pixel_delta_v;

    void initialise();
    Color ray_color(const Ray& r, int depth, const Hittable& world) const;
    Ray get_ray(int i, int j) const;
    Vec3 sample_square() const;
};