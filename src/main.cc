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

HittableList RandomScene() {
    HittableList world;

    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.Add(std::make_shared<Sphere>(Point3(0, -1000.0, 0), 1000, ground_material));

    for(int a = -11; a < 11; ++a) {
        for(int b = -11; b < 11; ++b) {
            auto choose_mat = RandomDouble();
            Point3 center(a + 0.9 * RandomDouble(), 0.2, b + 0.9 * RandomDouble());

            if ((center - Point3(4.0, 0.2, 0.0)).Length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // difffuse
                    auto albedo = Color::Random() * Color::Random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color::Random(0.5, 1.0);
                    auto fuzz = RandomDouble(0, 0.05);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                } else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                }
                world.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.Add(std::make_shared<Sphere>(Point3(0.0, 1.0, 0.0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.Add(std::make_shared<Sphere>(Point3(-4.0, 1.0, 0.0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.Add(std::make_shared<Sphere>(Point3(4.0, 1.0, 0.0), 1.0, material3));

    return world;
}

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
    const auto kAspectRatio = 3.0 / 2.0;
    const int kImageWidth = 1200;
    const int kImageHeight = static_cast<int>(kImageWidth / kAspectRatio);
    const int kSamplesPerPixel = 500;
    const int kMaxDepth = 50;

    // Camera
    const Point3 kLook_from(13.0, 2.0, 3.0);
    const Point3 kLook_at(0.0, 0.0, 0.0);
    const Point3 kVup(0.0, 1.0, 0.0);
    const auto kVfov = 20.0; // degrees
    auto focus_dist = 10.0;
    auto aperture = 0.1;
    const Camera cam(kLook_from, kLook_at, kVup, kVfov, kAspectRatio, aperture, focus_dist);

    // World
    auto world = RandomScene();
    auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left   = std::make_shared<Dielectric>(1.5);
    auto material_right  = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);

    world.Add(std::make_shared<Sphere>(Point3( 0.0, -100.5, -1.0 ), 100.0, material_ground));
    world.Add(std::make_shared<Sphere>(Point3( 0.0,    0.0, -1.0 ),    0.5, material_center));
    world.Add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),     0.5, material_left));
    world.Add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),    -0.3, material_left));
    world.Add(std::make_shared<Sphere>(Point3( 1.0,    0.0, -1.0 ),    0.5, material_right));

    // Render
    std::cout << "P3\n" << kImageWidth << ' ' << kImageHeight << "\n255\n";

    for (int j = kImageHeight-1; j >= 0; --j) {
        std::cerr << "\rPercent complete: " << 100*(1.0 - j/double(kImageHeight)) << "% " << std::flush;
        for (int i = 0; i < kImageWidth; ++i) {
            Color pixel_color(0.0, 0.0, 0.0);
            for (int s = 0; s < kSamplesPerPixel; ++s) {
                auto u = (i + RandomDouble()) / (kImageWidth - 1);
                auto v = (j + RandomDouble())/ (kImageHeight - 1);
                auto r = cam.GetRay(u, v);
                pixel_color += RayColor(r, world, kMaxDepth);
            }
            WriteColor(std::cout, pixel_color, kSamplesPerPixel);
        }
    }

    std::cerr << "\nDone\n";
}
