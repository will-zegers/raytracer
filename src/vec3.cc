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
