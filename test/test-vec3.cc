#include <cmath>
#include <iostream>
#include <random>
#include <ctime>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "raytracer/vec3.h"
#include "raytracer/test/util.h"


TEST_CASE("creating a default vec3", "[vec3]") {
    Vec3 v;

    REQUIRE(v.x() == 0);
    REQUIRE(v.y() == 0);
    REQUIRE(v.z() == 0);
}

TEST_CASE("testing some basic vec3 operations", "[vec3]") {
    double x1 = 1;
    double y1 = 2;
    double z1 = 3;
    Vec3 v1(x1, y1, z1);

    CHECK(v1.x() == x1);
    CHECK(v1.y() == y1);
    CHECK(v1.z() == z1);

    SECTION("negating the vector") {
        Vec3 v2 = -v1;

        CHECK(v2.x() == -x1);
        CHECK(v2.y() == -y1);
        CHECK(v2.z() == -z1);
    }

    SECTION("adding, subtracting, and dotting vectors") {
        auto x3 = static_cast<double>(rand() % 100);
        auto y3 = static_cast<double>(rand() % 100);
        auto z3 = static_cast<double>(rand() % 100);
        Vec3 v3(x3, y3, z3);

        SECTION("adding vectors") {
            Vec3 v4 = v1 + v3;

            CHECK(v4.x() == x1 + x3);
            CHECK(v4.y() == y1 + y3);
            CHECK(v4.z() == z1 + z3);
        }

        SECTION("subtracting vectors") {
            Vec3 v5 = v1 - v3;

            CHECK(v5.x() == x1 - x3);
            CHECK(v5.y() == y1 - y3);
            CHECK(v5.z() == z1 - z3);
        }

        SECTION("computing vector dot product") {
            auto expected = v1.x()*v3.x() + v1.y()*v3.y() + v1.z()*v3.z();
            auto dot = Dot(v1, v3);
            CHECK(dot == expected);
        }
    }

    SECTION("vector scaling, length, and unit vector") {
        auto t = static_cast<double>(rand() % 100);
        Vec3 v5 = t*v1;

        REQUIRE(v5.x() == Catch::Approx(t * x1));
        REQUIRE(v5.y() == Catch::Approx(t * y1));
        REQUIRE(v5.z() == Catch::Approx(t * z1));

        Vec3 v6 = v1 / t;

        REQUIRE(v6.x() == Catch::Approx(x1 / t));
        REQUIRE(v6.y() == Catch::Approx(y1 / t));
        REQUIRE(v6.z() == Catch::Approx(z1 / t));

        auto expected_length = sqrt(x1*x1 + y1*y1 + z1*z1);
        REQUIRE(v1.Length() == expected_length);

        auto unit_vector = UnitVector(v1);
        CHECK(ApproxEqual(unit_vector, v1 / v1.Length()));
    }
}
