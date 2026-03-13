#pragma once

#include "Color.h"
#include "Hittable.h"
#include "Ray.h"

class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter([[maybe_unused]] const Ray& r,
                         [[maybe_unused]] const HitRecord& rec,
                         [[maybe_unused]] Color& attenuation,
                         [[maybe_unused]] Ray& scattered) const;
};

class Lambertian : public Material {
public:
    Lambertian(const Color& albedo);

    bool scatter([[maybe_unused]] const Ray& r, const HitRecord& rec, Color& attenuation,
                 Ray& scattered) const override;

private:
    Color m_albedo;
};

class Metal : public Material {
public:
    Metal(const Color& albedo, double fuzz);

    bool scatter(const Ray& r, const HitRecord& rec, Color& attenuation,
                 Ray& scattered) const override;

private:
    Color m_albedo;
    double m_fuzz;
};

class Dielectric : public Material {
public:
    Dielectric(double refraction_index);

    bool scatter(const Ray& r, const HitRecord& rec, Color& attenuation,
                 Ray& scattered) const override;

private:
    static double reflectance(double cosine, double refraction_index);
    double m_refraction_index;
};