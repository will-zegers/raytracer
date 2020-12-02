#pragma once

#include <cmath>
#include <iostream>

class Vec3 {
    public:
        Vec3() : e{0, 0, 0} {}
        Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }

        double Length() const {
            return sqrt(lengthSquared());
        }

        // Vec3 utility friend functions
        friend inline std::ostream& operator<<(std::ostream&, const Vec3&);
        friend inline Vec3 operator+(const Vec3&, const Vec3&);
        friend inline Vec3 operator-(const Vec3&, const Vec3&);
        friend inline Vec3 operator*(double, const Vec3&);
        friend inline double Dot(const Vec3&, const Vec3&);

    private:
        double lengthSquared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        double e[3];
}; // class Vec3

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << "Vec3(" << v.e[0] << ", " << v.e[1] << ", " << v.e[2] << ")";
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vec3 operator*(const Vec3 &v, double t) {
    return t * v;
}

inline Vec3 operator/(const Vec3 &v, double t) {
    return (1/t) * v;
}

inline double Dot(const Vec3 &u, const Vec3 &v) {
    return u.e[0]*v.e[0] + u.e[1]*v.e[1] + u.e[2]*v.e[2];
}

inline Vec3 UnitVector(Vec3 v) {
    return v / v.Length();
}

using Point3 = Vec3;
