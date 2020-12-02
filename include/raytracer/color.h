#pragma once

#include <iostream>

#include "raytracer/vec3.h"

class Color {
    public:
        Color(double r, double g, double b) : e{r, g, b} {}

        double r() const { return e[0]; }
        double g() const { return e[1]; }
        double b() const { return e[2]; }

        friend inline Color operator+(const Color&, const Color&);
        friend inline Color operator+(const Color&, const Vec3&);
        friend inline Color operator+(const Vec3&, const Color&);
        friend inline Color operator*(double, const Color&);

        Color& operator+=(const Color& c) {
            e[0] += c.r();
            e[1] += c.g();
            e[2] += c.b();
            return *this;
        }

    private:
        double e[3];
};

inline double clamp(double x, double min, double max) {
    if (x < min) { return min; }
    if (x > max) { return max; }
    return x;
}

void WriteColor(std::ostream &out, Color pixel_color, int samples_per_pixel) {
    auto scale = 1.0 / samples_per_pixel;

    // Divide the color by the number of samples.
    auto r = pixel_color.r()*scale;
    auto g = pixel_color.g()*scale;
    auto b = pixel_color.b()*scale;

    // Write the translated [0,255] value of each Color component.
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

inline Color operator+(const Color& c1, const Color& c2) {
    return Color(c1.e[0] + c2.e[0], c1.e[1] + c2.e[1], c1.e[2] + c2.e[2]);
}

inline Color operator+(const Color& c, const Vec3& v) {
    return Color(c.e[0] + v.x(), c.e[1] + v.y(), c.e[2] + v.z());
}

inline Color operator+(const Vec3& v, const Color& c) {
    return c + v;
}

inline Color operator*(double t, const Color& c) {
    return Color(t*c.e[0], t*c.e[1], t*c.e[2]);
}
