#pragma once

#include "raytracer/ray.h"
#include "raytracer/vec3.h"

struct HitRecord {
    Point3 p;
    Vec3 normal;
    double t;
    bool front_face;

    inline void SetFaceNormal(const Ray& r, const Vec3& outward_normal) {
        front_face = Dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable {
    public: 
        virtual bool Hit(const Ray&, double, double, HitRecord&) const = 0;
};

inline std::ostream& operator<<(std::ostream& out, HitRecord& rec) {
    return out << "HitRecord("
               << "p=" << rec.p << ", "
               << "normal=" << rec.normal << ", "
               << "t=" << rec.t << ", "
               << "front_face=" << rec.front_face << ")";
    return out;
}
