#ifndef COLOR_H
#define COLOR_H

#include "constants.h"
#include "vec3.h"
#include <format>
#include <gsl/util>
#include <iostream>

// we have some overlap with vec3
// we don't specify that the values are in the range 0 to 255 as in a ray tracer
// this values will propably don't apply in the computation. We will garantie
// this range somewhere else in the code.
class color
{
  private:
    // mostly this values will be in the range [0,1] and then transform to the
    // range [0,255].
    double m_x{};
    double m_y{};
    double m_z{};

  public:
    color() : m_x{0}, m_y{0}, m_z{0} {};
    color(double x, double y, double z) : m_x{x}, m_y{y}, m_z{z} {};

    // define getter and setter
    double get_x() const { return m_x; }
    void set_x(double x) { m_x = x; }

    double get_y() const { return m_y; }
    void set_y(double y) { m_y = y; }

    double get_z() const { return m_z; }
    void set_z(double z) { m_z = z; }

    color& operator+=(const color c2)
    {
        m_x += c2.get_x();
        m_y += c2.get_y();
        m_z += c2.get_z();

        return *this;
    }

    static color random()
    {
        return color{config::random_double(), config::random_double(),
                     config::random_double()};
    }

    static color random(double min, double max)
    {
        return color{config::random_double(min, max),
                     config::random_double(min, max),
                     config::random_double(min, max)};
    }

    friend color operator*(const color& u, const color& v)
    {
        return color{u.m_x * v.m_x, u.m_y * v.m_y, u.m_z * v.m_z};
    }

    friend color operator*(double a, color c1)
    {
        return color{c1.get_x() * a, c1.get_y() * a, c1.get_z() * a};
    }

    friend color operator*(color c1, double a) { return a * c1; }

    friend color operator+(color c1, color c2)
    {
        return color{c1.get_x() + c2.get_x(), c1.get_y() + c2.get_y(),
                     c1.get_z() + c2.get_z()};
    }

    friend color operator+(vec3 v, color c)
    {
        return color{v.get_x() + c.get_x(), v.get_y() + c.get_y(),
                     v.get_z() + c.get_z()};
    }
};

// helper function
color pointToColor(point3 p)
{
    double length = std::hypot(p.get_x(), p.get_y(), p.get_z());
    return 0.5 * color{p.get_x() / length + 1, p.get_y() / length + 1,
                       p.get_z() / length + 1};
}

inline double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return std::sqrt(linear_component);

    return 0;
}

// this transform the double value in the range [0,1] value of a color to a
// int in the range [0,255]
int transformColorValue(const double colorNum)
{
    static const interval intensity(0.000, 0.999);
    return gsl::narrow_cast<int>(config::maxDoubleColorValue *
                                 intensity.clamp(linear_to_gamma(colorNum)));
}

// Formatter für std::format / std::print / std::println
template <> struct std::formatter<color> : std::formatter<double>
{
    // parse() wird von formatter<double> geerbt

    auto format(const color& v, std::format_context& ctx) const
    {
        auto out = ctx.out(); // Iterator auf die Ausgabe
        out =
            std::formatter<double>::format(transformColorValue(v.get_x()), ctx);
        out = std::format_to(out, " ");
        out =
            std::formatter<double>::format(transformColorValue(v.get_y()), ctx);
        out = std::format_to(out, " ");
        out =
            std::formatter<double>::format(transformColorValue(v.get_z()), ctx);
        return out;
    }
};

inline std::ostream& operator<<(std::ostream& out, const color& vec)
{
    return out << std::format("{}", vec);
}

#endif
