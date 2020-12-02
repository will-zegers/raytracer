#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

#include "raytracer/camera.h"
#include "raytracer/color.h"
#include "raytracer/hittable_list.h"
#include "raytracer/ray.h"
#include "raytracer/sphere.h"
#include "raytracer/vec3.h"

const double kInfinity = std::numeric_limits<double>::infinity();

inline double RandomDouble() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

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
    const int kSamplesPerPixel = 40;

    // Camera
    const auto origin = Point3(0.0, 0.0, 0.0);
    const auto viewport_height = 2.0;
    const auto focal_length = 1.0;
    const Camera cam(origin, kAspectRatio, viewport_height, focal_length);

    // World
    HittableList world;
    world.Add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.Add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Render
    std::cout << "P3\n" << kImageWidth << ' ' << kImageHeight << "\n255\n";

    for (int j = kImageHeight-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < kImageWidth; ++i) {
            Color pixel_color(0.0, 0.0, 0.0);
            for (int s = 0; s < kSamplesPerPixel; ++s) {
                auto u = (i + RandomDouble()) / (kImageWidth - 1);
                auto v = (j + RandomDouble())/ (kImageHeight - 1);
                auto r = cam.get_ray(u, v);
                pixel_color += RayColor(r, world);
            }
            WriteColor(std::cout, pixel_color, kSamplesPerPixel);
        }
    }

    std::cerr << "\nDone\n";
}
