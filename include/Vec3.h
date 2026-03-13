#pragma once

#include <array>
#include <cmath>
#include <iostream>

class Vec3 {
public:
    Vec3();
    Vec3(double x, double y, double z);

    static Vec3 gen_random(int min, int max);
    static Vec3 gen_random();

    double& x();
    double x() const;
    double& y();
    double y() const;
    double& z();
    double z() const;
    double length() const;
    double length_squared() const;
    bool near_zero() const;
    Vec3 cross(const Vec3& o) const;
    Vec3 operator+(const Vec3& o) const;
    Vec3 operator-() const;
    Vec3 operator-(const Vec3& o) const;
    Vec3 operator*(const Vec3& o) const;
    Vec3 operator*(double t) const;
    Vec3 operator/(double t) const;
    Vec3& operator+=(const Vec3& o);
    Vec3& operator*=(double t);
    Vec3& operator/=(double t);

private:
    std::array<double, 3> m_e;
};

std::ostream& operator<<(std::ostream& out, const Vec3& v);
Vec3 operator*(double t, const Vec3& o);

inline double dot(const Vec3& u, const Vec3& v) {
    return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

inline Vec3 unit_vector(const Vec3& v) { return v / v.length(); }

inline Vec3 random_unit_vector() {
    // Rejection method: Reject bad vector samples until we find a good one.
    while (true) {
        auto p{Vec3::gen_random(-1, 1)};
        auto len_sq{p.length_squared()};

        if (1e-160 < len_sq && len_sq <= 1)
            return p / std::sqrt(len_sq);
    }
}

inline Vec3 random_on_hemisphere(const Vec3& normal) {
    auto on_unit_sphere{random_unit_vector()};
    // invert the vector (not on hemisphere)
    return (dot(on_unit_sphere, normal) > 0.0) ? on_unit_sphere : -on_unit_sphere;
}

inline Vec3 reflect(const Vec3& v, const Vec3& n) { return v - 2 * dot(v, n) * n; }