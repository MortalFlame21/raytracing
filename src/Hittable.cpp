#include <cmath>

#include "Hittable.h"

// Start HitRecord
void HitRecord::set_face_normal(const Ray& r, const Vec3& outward_normal) {
    const auto front_face{dot(r.direction(), outward_normal) < 0};
    // either ray is inside the sphere or outside.
    m_normal = front_face ? outward_normal : -outward_normal;
}
// End HitRecord

// Start Sphere
Sphere::Sphere() : m_center{}, m_radius{} {};

Sphere::Sphere(const Vec3& center, double radius)
    : m_center{center}, m_radius{std::fmax(0, radius)} {}

bool Sphere::hit(const Ray& r, double ray_t_min, double ray_t_max, HitRecord& rec) const {
    Vec3 oc{m_center - r.origin()};
    auto a{r.direction().length_squared()};
    auto h{dot(r.direction(), oc)};
    auto c{oc.length_squared() - m_radius * m_radius};
    auto discriminant{h * h - a * c};

    if (discriminant < 0)
        return false;

    auto sqrt_d{std::sqrt(discriminant)};

    auto root{(h - sqrt_d) / a};
    if (root < ray_t_min || root >= ray_t_max) {
        root = (h + sqrt_d) / a;
        if (root < ray_t_min || root >= ray_t_max)
            return false;
    }

    rec.m_time = root;
    rec.m_point = r.at(rec.m_time);
    Vec3 outward_normal{(rec.m_point - m_center) / m_radius};
    rec.set_face_normal(r, outward_normal);

    return true;
}
// End Sphere

// Start HittableList
HittableList::HittableList() : m_objects{} {}

HittableList::HittableList(std::vector<std::shared_ptr<Hittable>> objects)
    : m_objects{objects} {}

void HittableList::clear() { m_objects.clear(); }

void HittableList::push_back(std::shared_ptr<Hittable> object) {
    m_objects.push_back(object);
}

bool HittableList::hit(const Ray& r, double ray_t_min, double ray_t_max,
                       HitRecord& rec) const {
    HitRecord temp_rec{};
    bool hit_anything{};
    auto closest_so_far{ray_t_max};

    for (const auto& o : m_objects) {
        if (o->hit(r, ray_t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.m_time;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
// End HittableList