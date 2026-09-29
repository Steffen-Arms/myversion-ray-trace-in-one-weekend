#ifndef INTERVAL_H
#define INTERVAL_H

#include "constants.h"

class interval
{
  public:
    double m_min, m_max;

    interval()
        : m_min{+config::infinity}, m_max{-config::infinity}
    {} // Default interval is empty

    interval(double min, double max) : m_min{min}, m_max{max} {}

    double size() const { return m_max - m_min; }

    bool contains(double x) const { return m_min <= x && x <= m_max; }

    bool surrounds(double x) const { return m_min < x && x < m_max; }

    double clamp(double x) const
    {
        if (x < m_min)
            return m_min;
        if (x > m_max)
            return m_max;
        return x;
    }

    static const interval s_empty, s_universe;
};

const interval interval::s_empty =
    interval(+config::infinity, -config::infinity);
const interval interval::s_universe =
    interval(-config::infinity, +config::infinity);

#endif
