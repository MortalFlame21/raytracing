#include <cmath>

#include "Vec3.h"

Vec3::Vec3() : m_e{{}} {}

Vec3::Vec3(double x, double y, double z) : m_e{{x, y, z}} {}

double& Vec3::x() { return m_e[0]; }
double Vec3::x() const { return m_e[0]; }

double& Vec3::y() { return m_e[1]; }
double Vec3::y() const { return m_e[1]; }

double& Vec3::z() { return m_e[2]; }
double Vec3::z() const { return m_e[2]; }

double Vec3::length() const { return std::sqrt(length_squared()); }

double Vec3::length_squared() const { return x() * x() + y() * y() + z() * z(); }

Vec3 Vec3::cross(const Vec3& o) const {
    return Vec3(y() * o.z() - z() * o.y(), z() * o.x() - x() * o.z(),
                x() * o.y() - y() * o.x());
}

Vec3 Vec3::operator+(const Vec3& o) const {
    return Vec3(x() + o.x(), y() + o.y(), z() + o.z());
}

Vec3 Vec3::operator-() const { return Vec3(-x(), -y(), -z()); }

Vec3 Vec3::operator-(const Vec3& o) const {
    return Vec3(x() - o.x(), y() - o.y(), z() - o.z());
}

Vec3 Vec3::operator*(const Vec3& o) const {
    return Vec3(x() * o.x(), y() * o.y(), z() - o.z());
}

Vec3 Vec3::operator*(double t) const { return t * (*this); }

Vec3 Vec3::operator/(double t) const { return (1 / t) * (*this); }

Vec3& Vec3::operator+=(const Vec3& o) {
    x() += o.x();
    y() += o.y();
    z() += o.z();
    return *this;
}

Vec3& Vec3::operator*=(double t) {
    x() *= t;
    y() *= t;
    z() *= t;
    return *this;
}

Vec3& Vec3::operator/=(double t) { return (*this) *= (1 / t); }

std::ostream& operator<<(std::ostream& out, const Vec3& v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

Vec3 operator*(double t, const Vec3& o) { return Vec3(t * o.x(), t * o.y(), t * o.z()); }