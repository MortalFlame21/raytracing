#include "Material.h"

// Start Material
bool Material::scatter(const Ray& r, const HitRecord& rec, Color& attenuation,
                       Ray& scattered) const {
    return false;
}
// End Material

// Start Lambertian
Lambertian::Lambertian(const Color& albedo) : m_albedo{albedo} {}

bool Lambertian::scatter(const Ray& r, const HitRecord& rec, Color& attenuation,
                         Ray& scattered) const {
    auto scatter_direction{rec.m_normal + random_unit_vector()};
    scattered = Ray(rec.m_point, scatter_direction);
    attenuation = m_albedo;
    return true;
}
// End Lambertian