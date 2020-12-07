#include <cmath>
#include <iostream>
#include <memory>

#include "raytracer/camera.h"
#include "raytracer/color.h"
#include "raytracer/hittable_list.h"
#include "raytracer/material.h"
#include "raytracer/ray.h"
#include "raytracer/sphere.h"
#include "raytracer/util.h"
#include "raytracer/vec3.h"

Color RayColor(const Ray& r, const Hittable& world, int depth) {
    if (depth <= 0) { return Color(0, 0, 0); }
    HitRecord rec;
    if (world.Hit(r, 0.001, kInfinity, rec)) {
        Ray scattered;
        Color attenuation;
        if (rec.mat_ptr->Scatter(r, rec, attenuation, scattered)) {
            return attenuation * RayColor(scattered, world, depth - 1);
        }
    }
    Vec3 unit_direction = UnitVector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}

int main() {
    // Image
    const auto kAspectRatio = 16.0 / 9.0;
    const int kImageWidth = 1080;
    const int kImageHeight = static_cast<int>(kImageWidth / kAspectRatio);
    const int kSamplesPerPixel = 200;
    const int kMaxDepth = 50;

    // Camera
    const auto origin = Point3(0.0, 0.0, 0.0);
    const auto viewport_height = 2.0;
    const auto focal_length = 1.0;
    const Camera cam(origin, kAspectRatio, viewport_height, focal_length);

    // World
    HittableList world;
    auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left = std::make_shared<Dialectric>(1.5);
    auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);

    world.Add(std::make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.Add(std::make_shared<Sphere>(Point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.Add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.Add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),  -0.4, material_left));
    world.Add(std::make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, material_right));

    // Render
    std::cout << "P3\n" << kImageWidth << ' ' << kImageHeight << "\n255\n";

    for (int j = kImageHeight-1; j >= 0; --j) {
        std::cerr << "\rPercent complete: " << 100*(1.0 - j/double(kImageHeight)) << "% " << std::flush;
        for (int i = 0; i < kImageWidth; ++i) {
            Color pixel_color(0.0, 0.0, 0.0);
            for (int s = 0; s < kSamplesPerPixel; ++s) {
                auto u = (i + RandomDouble()) / (kImageWidth - 1);
                auto v = (j + RandomDouble())/ (kImageHeight - 1);
                auto r = cam.get_ray(u, v);
                pixel_color += RayColor(r, world, kMaxDepth);
            }
            WriteColor(std::cout, pixel_color, kSamplesPerPixel);
        }
    }

    std::cerr << "\nDone\n";
}
