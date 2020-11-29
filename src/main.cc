#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

#include "raytracer/color.h"
#include "raytracer/hittable_list.h"
#include "raytracer/ray.h"
#include "raytracer/sphere.h"
#include "raytracer/vec3.h"

const double kInfinity = std::numeric_limits<double>::infinity();

Color RayColor(const Ray& r, const Hittable& world) {
    HitRecord rec;
    if (world.Hit(r, 0, kInfinity, rec)) {
        return 0.5 * (rec.normal + Color(1, 1, 1));
    }
    Vec3 unit_direction = UnitVector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}

int main() {
    // Image
    const auto kAspectRatio = 16.0 / 9.0;
    const int kImageWidth = 400;
    const int kImageHeight = static_cast<int>(kImageWidth / kAspectRatio);

    // Camera
    const auto kViewPortHeight = 2.0;
    const auto kViewPortWidth = kAspectRatio * kViewPortHeight;
    const auto kFocalLength = 1.0;

    const auto kOrigin = Point3(0, 0, 0);
    const auto kHorizontal = Vec3(kViewPortWidth, 0, 0);
    const auto kVertical = Vec3(0, kViewPortHeight, 0);
    const auto kLowerLeftCorner = kOrigin - kHorizontal/2 - kVertical/2 - Vec3(0, 0, kFocalLength);

    // World
    HittableList world;
    world.Add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.Add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Render
    std::cout << "P3\n" << kImageWidth << ' ' << kImageHeight << "\n255\n";

    for (int j = kImageHeight-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < kImageWidth; ++i) {
            auto u = double(i) / (kImageWidth - 1);
            auto v = double(j) / (kImageHeight - 1);
            Ray r(kOrigin, kLowerLeftCorner + u*kHorizontal + v*kVertical - kOrigin);
            Color pixel_color = RayColor(r, world);
            WriteColor(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone\n";
}
