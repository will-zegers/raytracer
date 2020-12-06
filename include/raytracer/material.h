#pragma once

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
