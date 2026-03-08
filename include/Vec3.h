#pragma once

#include <array>
#include <iostream>

class Vec3 {
public:
    Vec3();
    Vec3(double x, double y, double z);

    double& x();
    double x() const;
    double& y();
    double y() const;
    double& z();
    double z() const;
    double length() const;
    double length_squared() const;
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

inline double dot(const Vec3& u, const Vec3& v) {
    return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}
inline Vec3 unit_vector(const Vec3& v) { return v / v.length(); }
std::ostream& operator<<(std::ostream& out, const Vec3& v);
Vec3 operator*(double t, const Vec3& o);