#include "raytracer/color.h"
#include "raytracer/hittable.h"
#include "raytracer/material.h"
#include "raytracer/ray.h"
#include "raytracer/vec3.h"

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
