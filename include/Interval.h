#pragma once

#include "Util.h"

class Interval {
public:
    double m_min;
    double m_max;

    Interval();
    Interval(double min, double max);

    double size() const;
    double contains(double x) const;
    bool surrounds(double x) const;
    double clamp(double x) const;

    static const Interval empty;
    static const Interval universe;
};

inline const Interval Interval::empty{+infinity, -infinity};
inline const Interval Interval::universe{-infinity, +infinity};