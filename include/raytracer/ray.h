#pragma once

#include "raytracer/vec3.h"

class Ray {
    public:
        Ray(const Point3& origin, const Vec3& direction)
            :origin_(origin), direction_(direction)
        {}

        Point3 origin() const { return origin_; }
        Vec3 direction() const { return direction_; }

        Point3 At(double t) const {
            return origin_ + t*direction_;
        }

        friend inline std::ostream& operator<<(std::ostream&, const Ray&);

    private:
        Point3 origin_;
        Vec3 direction_;
};

inline std::ostream& operator<<(std::ostream& out, const Ray& r) {
    return out << "Ray(" << r.origin_ << ", " << r.direction_ << ")";
}
