#include "raytracer/vec.h"

Vec3 RandomInUnitSphere() {
    while(true) {
        auto p = Vec3::random(-1, 1);
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
