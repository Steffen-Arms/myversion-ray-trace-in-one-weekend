#ifndef POINT3_H
#define POINT3_H

#include "vec3.h"
#include <format>

// we have lot of overlap with the vec3 class but some operations for vectors
// don't make sense for points so we make a own definition for them.
class point3
{
  private:
    double m_x{};
    double m_y{};
    double m_z{};

  public:
    point3() : m_x{0}, m_y{0}, m_z{0} {};
    point3(double x, double y, double z) : m_x{x}, m_y{y}, m_z{z} {};

    // define getter and setter
    double get_x() const { return m_x; }
    void set_x(double x) { m_x = x; }

    double get_y() const { return m_y; }
    void set_y(double y) { m_y = y; }

    double get_z() const { return m_z; }
    void set_z(double z) { m_z = z; }

    // define unary operators
    point3 operator-() const { return point3{-m_x, -m_y, -m_z}; }

    point3& operator+=(const vec3& v)
    {
        m_x += v.get_x();
        m_y += v.get_y();
        m_z += v.get_z();
        return *this;
    }

    point3& operator*=(double t)
    {
        m_x *= t;
        m_y *= t;
        m_z *= t;
        return *this;
    }

    point3& operator/=(double t) { return *this *= 1 / t; }

    // define the length of from the point to  the origin in euclidian distance
    double length() const { return std::hypot(m_x, m_y, m_z); }

    // declare friend binary operator functions

    friend point3 operator+(const point3& u, const vec3& v)
    {
        return point3{u.m_x + v.get_x(), u.m_y + v.get_y(), u.m_z + v.get_z()};
    }

    friend point3 operator+(const vec3& v, const point3& u) { return u + v; }

    friend point3 operator-(const point3& u, const vec3& v) { return u + (-v); }

    friend vec3 operator-(const point3& u, const point3& v)
    {
        return vec3{u.get_x() - v.get_x(), u.get_y() - v.get_y(),
                    u.get_z() - v.get_z()};
    }

    friend point3 operator*(double t, const point3& v)
    {
        return point3{v.m_x * t, v.m_y * t, v.m_z * t};
    }

    friend point3 operator*(const point3& v, double t) { return t * v; }

    friend point3 operator/(const point3& v, double t) { return (1 / t) * v; }
};

// Formatter für std::format / std::print / std::println
template <> struct std::formatter<point3> : std::formatter<double>
{
    // parse() wird von formatter<double> geerbt

    auto format(const point3& v, std::format_context& ctx) const
    {
        auto out = ctx.out(); // Iterator auf die Ausgabe
        out = std::format_to(out, "(");
        out = std::formatter<double>::format(v.get_x(), ctx);
        out = std::format_to(out, ", ");
        out = std::formatter<double>::format(v.get_y(), ctx);
        out = std::format_to(out, ", ");
        out = std::formatter<double>::format(v.get_z(), ctx);
        return std::format_to(out, ")"); // Iterator zurückgeben
    }
};

inline std::ostream& operator<<(std::ostream& out, const point3& vec)
{
    return out << std::format("{}", vec);
}

#endif
