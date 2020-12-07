#include <cmath>

#include "raytracer/vec3.h"

Vec3 RandomInUnitSphere() {
    while(true) {
        auto p = Vec3::Random(-1, 1);
        if (p.LengthSquared() >= 1) { continue; }
        return p;
    }
}

Vec3 RandomUnitVector() {
    return UnitVector(RandomInUnitSphere());
}

Vec3 RandomInHemisphere(const Vec3& normal) {
    Vec3 InUnitSphere = RandomInUnitSphere();
    if (Dot(InUnitSphere, normal) > 0.0) {
        return InUnitSphere;
    } else {
        return -InUnitSphere;
    }
}

Vec3 Reflect(const Vec3& v, const Vec3& n) {
    return v - 2*Dot(v, n)*n;
}

Vec3 Refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(Dot(-uv, n), 1.0);
    Vec3 r_out_perp = etai_over_etat * (uv + cos_theta*n);
    Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.LengthSquared())) * n;
    return r_out_perp + r_out_parallel;
}
