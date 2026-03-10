#pragma once

#include "Ray.h"

struct HitRecord {
    Vec3 m_point;
    Vec3 m_normal;
    double m_time;
};

class Hittable {
public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray& r, double ray_t_min, double ray_t_max,
                     HitRecord& rec) const = 0;
};

class Sphere : public Hittable {
public:
    Sphere();
    Sphere(const Vec3& center, double radius);
    bool hit(const Ray& r, double ray_t_min, double ray_t_max,
             HitRecord& rec) const override;

private:
    Vec3 m_center;
    double m_radius;
};