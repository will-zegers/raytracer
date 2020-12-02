#include <catch2/catch_test_macros.hpp>

#include "raytracer/hittable.h"
#include "raytracer/ray.h"
#include "raytracer/vec3.h"
#include "raytracer/test/util.h"

TEST_CASE("test HitRecord struct functionality", "[hittable]") {
    Vec3 outward_normal(0.110494, 0.8333579, 0.541236);

    HitRecord rec;
    rec.p = Vec3(-0.055247, 0.41679, -0.729382);
    rec.t = 0.729382;

    double ray_direction_x = 0.0757449;
    double ray_direction_y = 0.571429;
    double ray_direction_z = 1;

    SECTION("checking ray direction x, y, z in same direction as outward_normal") {
        Ray r(Point3(0, 0, 0), Vec3(ray_direction_x, ray_direction_y,
                                    ray_direction_z));
        rec.SetFaceNormal(r, outward_normal);
        CHECK(rec.front_face == false);
        REQUIRE(ApproxEqual(rec.normal, -outward_normal));
    }

    SECTION("reverse ray direction x component, outward normal flips") {
        Ray r(Point3(0, 0, 0), Vec3(-ray_direction_x, ray_direction_y,
                                    ray_direction_z));
        rec.SetFaceNormal(r, outward_normal);
        CHECK(rec.front_face == false);
        REQUIRE(ApproxEqual(rec.normal, -outward_normal));
    }

    SECTION("reverse ray direction y component, outward normal flips") {
        Ray r(Point3(0, 0, 0), Vec3(ray_direction_x, -ray_direction_y,
                                    ray_direction_z));
        rec.SetFaceNormal(r, outward_normal);
        CHECK(rec.front_face == false);
        REQUIRE(ApproxEqual(rec.normal, -outward_normal));
    }

    SECTION("reverse ray direction z component, outward normal unchanged") {
        Ray r(Point3(0, 0, 0), Vec3(ray_direction_x, ray_direction_y,
                                    -ray_direction_z));
        rec.SetFaceNormal(r, outward_normal);
        CHECK(rec.front_face == true);
        REQUIRE(ApproxEqual(rec.normal, outward_normal));
    }

    SECTION("reverse ray direction x-y components, outward normal flips") {
        Ray r(Point3(0, 0, 0), Vec3(-ray_direction_x, -ray_direction_y,
                                    ray_direction_z));
        rec.SetFaceNormal(r, outward_normal);
        CHECK(rec.front_face == false);
        REQUIRE(ApproxEqual(rec.normal, -outward_normal));
    }

    SECTION("reverse ray direction x-z components, outward normal unchanged") {
        Ray r(Point3(0, 0, 0), Vec3(-ray_direction_x, ray_direction_y,
                                    -ray_direction_z));
        rec.SetFaceNormal(r, outward_normal);
        CHECK(rec.front_face == true);
        REQUIRE(ApproxEqual(rec.normal, outward_normal));
    }

    SECTION("reverse ray direction y-z components, outward normal unchanged") {
        Ray r(Point3(0, 0, 0), Vec3(ray_direction_x, -ray_direction_y,
                                    -ray_direction_z));
        rec.SetFaceNormal(r, outward_normal);
        CHECK(rec.front_face == true);
        REQUIRE(ApproxEqual(rec.normal, outward_normal));
    }

    SECTION("reverse ray direction x-y-z components, outward normal unchanged") {
        Ray r(Point3(0, 0, 0), Vec3(-ray_direction_x, -ray_direction_y,
                                    -ray_direction_z));
        rec.SetFaceNormal(r, outward_normal);
        CHECK(rec.front_face == true);
        REQUIRE(ApproxEqual(rec.normal, outward_normal));
    }
}

