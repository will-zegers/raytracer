#pragma once

#include <cmath>
#include <iostream>

#include "raytracer/vec3.h"

class Color {
    public:
        Color() {}
        Color(double r, double g, double b) : e{r, g, b} {}

        double r() const { return e[0]; }
        double g() const { return e[1]; }
        double b() const { return e[2]; }

        friend inline Color operator+(const Color&, const Color&);
        friend inline Color operator+(const Color&, const Vec3&);
        friend inline Color operator+(const Vec3&, const Color&);
        friend inline Color operator*(const Color&, const Color&);
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

inline Color operator+(const Color& c1, const Color& c2) {
    return Color(c1.e[0] + c2.e[0], c1.e[1] + c2.e[1], c1.e[2] + c2.e[2]);
}

inline Color operator+(const Color& c, const Vec3& v) {
    return Color(c.e[0] + v.x(), c.e[1] + v.y(), c.e[2] + v.z());
}

inline Color operator+(const Vec3& v, const Color& c) {
    return c + v;
}

inline Color operator*(const Color& c1, const Color& c2) {
    return Color(c1.e[0] * c2.e[0], c1.e[1] * c2.e[1], c1.e[2] * c2.e[2]);
}

inline Color operator*(double t, const Color& c) {
    return Color(t*c.e[0], t*c.e[1], t*c.e[2]);
}

void WriteColor(std::ostream&, Color, int);
