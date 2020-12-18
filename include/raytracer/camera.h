#pragma once

#include <cmath>
#include <iostream>

#include "raytracer/ray.h"
#include "raytracer/vec3.h"
#include "raytracer/util.h"

class Camera {
    public:
        Camera(Point3 look_from, Point3 look_at, Vec3 vup, double vfov,
               double aspect_ratio, double aperture, double focus_dist)
        : kOrigin_(look_from)
        , kLens_radius_(aperture / 2)
    {
        auto theta = DegreesToRadians(vfov);
        auto viewport_height = 2.0 * tan(theta / 2);
        auto viewport_width = aspect_ratio * viewport_height;

        w_ = UnitVector(look_from - look_at);
        u_ = UnitVector(Cross(vup, w_));
        v_ = Cross(w_, u_);

        horizontal_ = focus_dist * viewport_width * u_;
        vertical_ = focus_dist * viewport_height * v_;
        lowerLeftCorner_ = kOrigin_ - horizontal_/2 - vertical_/2 - focus_dist*w_;
    }

    inline Ray GetRay(double s, double t) const {
        Vec3 rd = kLens_radius_ * RandomInUnitDisk();
        Vec3 offset = u_ * rd.x() + v_ * rd.y();

        auto direction = lowerLeftCorner_
            + s*horizontal_
            + t*vertical_
            - kOrigin_
            - offset;
        return Ray(kOrigin_ + offset, direction);
    }

    private:
        const Point3 kOrigin_;
        const double kLens_radius_;

        Vec3   horizontal_;
        Vec3   vertical_;
        Point3 lowerLeftCorner_;
        Vec3   u_;
        Vec3   v_;
        Vec3   w_;
};
