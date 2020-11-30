#include <catch2/catch_test_macros.hpp>

#include "raytracer/ray.h"
#include "raytracer/vec3.h"
#include "raytracer/test/util.h"

TEST_CASE("test ray class" "[ray]") {
    Point3 origin(0, 0, 0);
    Vec3 direction = UnitVector({2, 8, 16});

    Ray r(origin, direction);

    CHECK(ApproxEqual(r.origin(), origin));
    CHECK(ApproxEqual(r.direction(), direction));

    Vec3 expected(1.0, 4.0, 8.0);
    auto p = r.At(9);
    CHECK(ApproxEqual(p, expected));
}
