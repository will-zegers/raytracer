#pragma once

#include "raytracer/hittable.h"
#include "raytracer/vec3.h"

class Sphere : public Hittable {
    public:
        Sphere() {}
        Sphere(Point3 center, double r) : center_(center), radius_(r) {}

        virtual bool Hit(const Ray&, double, double, HitRecord&) const override;

    private:
        Point3 center_;
        double radius_;
};

bool Sphere::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    Vec3 oc = r.origin() - center_;
    auto a = Dot(r.direction(), r.direction());
    auto b = 2.0 * Dot(oc, r.direction());
    auto c = Dot(oc, oc) - radius_*radius_;

    auto discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        return false;
    }
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-b - sqrtd) / (2.0 * a);
    if (root < t_min || t_max < root) {
        root = (-b + sqrtd) / (2.0 * a);
        if (root < t_min || t_max < root) {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    Vec3 outward_normal = (rec.p - center_) / radius_;
    rec.SetFaceNormal(r, outward_normal);

    return true;
}
