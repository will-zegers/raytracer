#pragma once

#include <cmath>

#include "raytracer/color.h"
#include "raytracer/ray.h"

struct HitRecord;

class Material {
    public:
        virtual bool Scatter(const Ray&, const HitRecord&, Color&, Ray&) const = 0;
};

class Lambertian : public Material {
    public:
        Lambertian(const Color& albedo) : albedo_(albedo) {}

        virtual bool Scatter(const Ray&, const HitRecord&, Color&, Ray&) const override;

    private:
        Color albedo_;
};

class Metal : public Material {
    public:
        Metal(const Color& albedo, double fuzz)
            : albedo_(albedo), fuzz_(fuzz) {}

        virtual bool Scatter(const Ray&, const HitRecord&, Color&, Ray&) const override;
    private:
        Color albedo_;
        double fuzz_;
};

class Dielectric : public Material {
    public:
        Dielectric(double index_of_refraction) : ir_(index_of_refraction) {}

        virtual bool Scatter(const Ray&, const HitRecord&, Color&, Ray&) const override;
    private:
        static double Reflectance(double cosine, double ref_idx) {
            // Use Schlick's approximation for refectance
            auto r0 = (1 - ref_idx) / (1 + ref_idx);
            auto r0_sq = r0 * r0;
            return r0_sq + (1 - r0_sq)*pow((1 - cosine), 5);
        }

        double ir_;
};
