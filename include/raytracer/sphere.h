#pragma once

#include <memory>

#include "raytracer/hittable.h"
#include "raytracer/material.h"
#include "raytracer/vec3.h"

class Sphere : public Hittable {
    public:
        Sphere(Point3 center, double r, std::shared_ptr<Material> mat_ptr)
            : center_(center) , radius_(r) , mat_ptr_(mat_ptr) {}

        virtual bool Hit(const Ray&, double, double, HitRecord&) const override;

    private:
        Point3 center_;
        double radius_;
        std::shared_ptr<Material> mat_ptr_;
};
