#include "Interval.h"

Interval::Interval() : m_min{+infinity}, m_max{-infinity} {}

Interval::Interval(double min, double max) : m_min{min}, m_max{max} {}

double Interval::size() const { return m_max - m_min; }

double Interval::contains(double x) const { return m_min <= x && x <= m_max; }

bool Interval::surrounds(double x) const { return m_min < x && x < m_max; }