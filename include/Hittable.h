#pragma once

#include <memory>
#include <vector>

#include "Interval.h"
#include "Ray.h"

class Material;

class HitRecord {
public:
    void set_face_normal(const Ray& r, const Vec3& outward_normal);

    Vec3 m_point;
    Vec3 m_normal;
    std::shared_ptr<Material> m_material;
    double m_time;
};

class Hittable {
public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray& r, const Interval& ray_t, HitRecord& rec) const = 0;
};

class Sphere : public Hittable {
public:
    Sphere();
    Sphere(const Vec3& center, double radius);
    bool hit(const Ray& r, const Interval& ray_t, HitRecord& rec) const override;

private:
    Vec3 m_center;
    double m_radius;
    std::shared_ptr<Material> m_material;
};

class HittableList : public Hittable {
public:
    HittableList();
    HittableList(std::vector<std::shared_ptr<Hittable>> objects);

    void clear();
    void push_back(std::shared_ptr<Hittable> object);
    bool hit(const Ray& r, const Interval& ray_t, HitRecord& rec) const override;

private:
    std::vector<std::shared_ptr<Hittable>> m_objects;
};