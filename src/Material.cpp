#include "Material.h"

// Start Material
bool Material::scatter([[maybe_unused]] const Ray& r,
                       [[maybe_unused]] const HitRecord& rec,
                       [[maybe_unused]] Color& attenuation,
                       [[maybe_unused]] Ray& scattered) const {
    return false;
}
// End Material

// Start Lambertian
Lambertian::Lambertian(const Color& albedo) : m_albedo{albedo} {}

bool Lambertian::scatter([[maybe_unused]] const Ray& r, const HitRecord& rec,
                         Color& attenuation, Ray& scattered) const {
    auto scatter_direction{rec.m_normal + random_unit_vector()};

    if (scatter_direction.near_zero())
        scatter_direction = rec.m_normal;

    scattered = Ray(rec.m_point, scatter_direction);
    attenuation = m_albedo;
    return true;
}
// End Lambertian

// Start Metal
Metal::Metal(const Color& albedo, double fuzz) : m_albedo{albedo}, m_fuzz{fuzz} {}

bool Metal::scatter(const Ray& r, const HitRecord& rec, Color& attenuation,
                    Ray& scattered) const {
    auto reflected{reflect(r.direction(), rec.m_normal)};
    reflected = unit_vector(reflected) + (m_fuzz * random_unit_vector());
    scattered = Ray(rec.m_point, reflected);
    attenuation = m_albedo;
    return dot(scattered.direction(), rec.m_normal) > 0;
}
// End Metal

// Start Dielectric
Dielectric::Dielectric(double refraction_index) : m_refraction_index{refraction_index} {}

bool Dielectric::scatter(const Ray& r, const HitRecord& rec, Color& attenuation,
                         Ray& scattered) const {
    attenuation = Color(1.0, 1.0, 1.0);
    auto ri{rec.m_front_face ? (1.0 / m_refraction_index) : m_refraction_index};
    auto unit_dir{unit_vector(r.direction())};

    auto cos_theta{std::fmin(dot(-unit_dir, rec.m_normal), 1.0)};
    auto sin_theta{std::sqrt(1.0 - cos_theta * cos_theta)};
    // can't refract or reflectance > rand_double
    Vec3 dir{((ri * sin_theta > 1.0) || reflectance(cos_theta, ri) > gen_random_double())
                 ? reflect(unit_dir, rec.m_normal)
                 : refract(unit_dir, rec.m_normal, ri)};

    scattered = Ray(rec.m_point, dir);
    return true;
}

double Dielectric::reflectance(double cosine, double refraction_index) {
    // Schlick approximation
    auto r0{(1 - refraction_index) / (1 + refraction_index)};
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow(1 - cosine, 5);
}
// End Dielectric
