#pragma once

#include <iostream>

#include "raytracer/vec3.h"

class Color {
    public:
        Color() : e{0, 0, 0} {}
        Color(double r, double g, double b) : e{r, g, b} {}

        double r() { return e[0]; }
        double g() { return e[1]; }
        double b() { return e[2]; }

        friend inline Color operator+(const Color&, const Color&);
        friend inline Color operator+(const Color&, const Vec3&);
        friend inline Color operator+(const Vec3&, const Color&);
        friend inline Color operator*(double, const Color&);

    private:
        double e[3];
};

void WriteColor(std::ostream &out, Color pixel_Color) {
    // Write the translated [0,255] value of each Color component.
    out << static_cast<int>(255.999 * pixel_Color.r()) << ' '
        << static_cast<int>(255.999 * pixel_Color.g()) << ' '
        << static_cast<int>(255.999 * pixel_Color.b()) << '\n';
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