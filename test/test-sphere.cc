#include <limits>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "raytracer/hittable.h"
#include "raytracer/material.h"
#include "raytracer/ray.h"
#include "raytracer/sphere.h"
#include "raytracer/vec3.h"

#include "raytracer/test/util.h"

TEST_CASE("test sphere", "[sphere]") {
    auto center = Vec3(0.0, 0.0, -1.0);
    auto radius = 0.5;
    auto material = std::make_shared<Lambertian>(Color(1.0, 1.0, 1.0));
    Sphere s(center, radius, material);

    auto t_min = 0.0;
    auto t_max = std::numeric_limits<double>::infinity();

    SECTION("no real roots (ray doesn't hit sphere)") {
        Ray r(Vec3(0, 0, 0), Vec3(-0.556948, 0.964286, -1));
        HitRecord rec;

        CHECK_FALSE(s.Hit(r, t_min, t_max, rec));
    }

    SECTION("roots outside the acceptable range") {
        Ray r(Vec3(0, 0, 0), Vec3(1.36786, 0.919643, -1));
        HitRecord rec;

        CHECK_FALSE(s.Hit(r, t_min, t_max, rec));
    }

    SECTION("real root found (ray hits sphere)") {
        Ray r(Vec3(0, 0, 0), Vec3(-0.476747, 0.133929, -1));
        HitRecord rec;

        REQUIRE(s.Hit(r, t_min, t_max, rec));
        CHECK(rec.t == Catch::Approx(0.596629));
        CHECK(ApproxEqual(rec.p, Vec3(-0.284441, 0.0799059, -0.596629)));
        CHECK(ApproxEqual(rec.normal, Vec3(-0.568882, 0.159812, 0.806743)));
        CHECK(rec.front_face == true);
    }
}

