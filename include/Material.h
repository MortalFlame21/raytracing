#pragma once

#include "Color.h"
#include "Hittable.h"
#include "Ray.h"

class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& r, const HitRecord& rec, Color& attenuation,
                         Ray& scattered) const;
};

class Lambertian : public Material {
public:
    Lambertian::Lambertian(const Color& albedo);

    virtual bool scatter(const Ray& r, const HitRecord& rec, Color& attenuation,
                         Ray& scattered) const override;

private:
    Color m_albedo;
};
