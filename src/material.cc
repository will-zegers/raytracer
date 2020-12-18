#include <cmath>

#include "raytracer/color.h"
#include "raytracer/hittable.h"
#include "raytracer/material.h"
#include "raytracer/ray.h"
#include "raytracer/vec3.h"

#include "raytracer/util.h"

bool Lambertian::Scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation,
                         Ray& scattered) const {
    auto scatter_direction = rec.normal + RandomInHemisphere(rec.normal);

    // Catch degenerate scatter direction
    if (scatter_direction.NearZero()) {
        scatter_direction = rec.normal;
    }

    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo_;
    return true;
}

bool Metal::Scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation,
                    Ray& scattered) const {
    Vec3 reflected = Reflect(UnitVector(r_in.direction()), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz_*RandomInUnitSphere());
    attenuation = albedo_;
    return (Dot(scattered.direction(), rec.normal) > 0.0);
}

bool Dielectric::Scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation,
                         Ray& scattered) const {
    attenuation = Color(1.0, 1.0, 1.0);
    double refraction_ratio = rec.front_face ? (1.0 / ir_) : ir_;

    Vec3 unit_direction = UnitVector(r_in.direction());
    double cos_theta = fmin(Dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

    Vec3 direction;
    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    if (cannot_refract || Reflectance(cos_theta, refraction_ratio) > RandomDouble()) {
        direction = Reflect(unit_direction, rec.normal);
    } else {
        direction = Refract(unit_direction, rec.normal, refraction_ratio);
    }

    scattered = Ray(rec.p, direction);
    return true;
}
