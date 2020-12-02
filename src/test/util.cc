#include <catch2/catch_approx.hpp>

#include "raytracer/vec3.h"
#include "raytracer/test/util.h"

bool ApproxEqual(const Vec3& u, const Vec3& v) {
    auto approx_equal = u.x() == Catch::Approx(v.x())
        and u.y() == Catch::Approx(v.y())
        and u.z() == Catch::Approx(v.z());
    if (!approx_equal) {
        std::cerr << "Vector mismatch: " << std::endl;
        std::cerr << '\t' << u << " != " << v << std::endl;
    }
    return approx_equal;
}
