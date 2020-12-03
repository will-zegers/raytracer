#include <ctime>
#include <random>
#include <sstream>
#include <string>

#include <catch2/catch_test_macros.hpp>

#include "raytracer/color.h"
#include "raytracer/vec3.h"

const double random_double() {
    return rand() / double(RAND_MAX);
}

TEST_CASE("basic color operations", "[color]") {
    double r1 = 0.25;
    double g1 = 0.50;
    double b1 = 0.75;
    Color c1(r1, g1, b1);

    REQUIRE(c1.r() == r1);
    REQUIRE(c1.g() == g1);
    REQUIRE(c1.b() == b1);

    SECTION("adding colors") {
        auto r2 = random_double();
        auto g2 = random_double();
        auto b2 = random_double();

        Color c2 = c1 + Color(r2, g2, b2);

        REQUIRE(c2.r() == r1 + r2);
        REQUIRE(c2.g() == g1 + g2);
        REQUIRE(c2.b() == b1 + b2);
    }

    SECTION("scaling colors") {
        auto t = static_cast<double>(rand());
        auto c3 = t*c1; 

        REQUIRE(c3.r() == t * r1);
        REQUIRE(c3.g() == t * g1);
        REQUIRE(c3.b() == t * b1);
    }

    SECTION("adding a vector and a color") {
        auto x = static_cast<double>(rand());
        auto y = static_cast<double>(rand());
        auto z = static_cast<double>(rand());
        Vec3 v(x, y, z);

        Color c4 = c1 + v;
        REQUIRE(c4.r() == r1 + x);
        REQUIRE(c4.g() == g1 + y);
        REQUIRE(c4.b() == b1 + z);
    }

    SECTION("writing out a color's rgb components") {
        std::ostringstream out;

        SECTION("sample size 1") {
            auto sample_size = 1;

            Color c5(sample_size*r1, sample_size*g1, sample_size*b1);
            WriteColor(out, c5, sample_size);
        }

        SECTION("sample size 100") {
            auto sample_size = 100;

            Color c6(sample_size*r1, sample_size*g1, sample_size*b1);
            WriteColor(out, c6, sample_size);
        }

        int r, g, b;
        std::istringstream is(out.str());
        is >> r >> g >> b;

        CHECK(r == 128);
        CHECK(g == 181);
        CHECK(b == 221);
    }
}
