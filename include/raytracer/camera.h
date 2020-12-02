#pragma once

#include <iostream>

#include "raytracer/ray.h"
#include "raytracer/vec3.h"

class Camera {
    public:
        Camera(
            Point3 origin,
            double aspect_ratio,
            double viewport_height,
            double focal_length
        )
        : kOrigin_(origin)
        , kHorizontal_(Vec3(aspect_ratio*viewport_height, 0.0, 0.0))
        , kVertical_(Vec3(0.0, viewport_height, 0.0))
        , kLowerLeftCorner_(kOrigin_ - kHorizontal_/2 - kVertical_/2
                            - Vec3(0.0, 0.0, focal_length))
    {}

        inline Ray get_ray(double u, double v) const {
            auto direction = kLowerLeftCorner_
                + u*kHorizontal_
                + v*kVertical_
                - kOrigin_;
            return Ray(kOrigin_, direction);
        }

    private:
        const Point3 kOrigin_;
        const Vec3 kHorizontal_;
        const Vec3 kVertical_;
        const Point3 kLowerLeftCorner_;
};
