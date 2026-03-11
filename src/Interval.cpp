#include "Interval.h"

Interval::Interval() : m_min{+infinity}, m_max{-infinity} {}

Interval::Interval(double min, double max) : m_min{min}, m_max{max} {}

double Interval::size() const { return m_max - m_min; }

double Interval::contains(double x) const { return m_min <= x && x <= m_max; }

bool Interval::surrounds(double x) const { return m_min < x && x < m_max; }

double Interval::clamp(double x) const {
    if (x < m_min)
        return m_min;
    else if (x > m_max)
        return m_max;
    return x;
}