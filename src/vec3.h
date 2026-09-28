#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <format>
#include <ostream>

class vec3
{
  private:
    double m_x{};
    double m_y{};
    double m_z{};

  public:
    vec3() : m_x{0}, m_y{0}, m_z{0} {};
    vec3(double x, double y, double z) : m_x{x}, m_y{y}, m_z{z} {};

    // define getter and setter
    double get_x() const { return m_x; }
    void set_x(double x) { m_x = x; }

    double get_y() const { return m_y; }
    void set_y(double y) { m_y = y; }

    double get_z() const { return m_z; }
    void set_z(double z) { m_z = z; }

    // define unary operators
    vec3 operator-() const { return vec3{-m_x, -m_y, -m_z}; }

    vec3& operator+=(const vec3& v)
    {
        m_x += v.m_x;
        m_y += v.m_y;
        m_z += v.m_z;
        return *this;
    }

    vec3& operator*=(double t)
    {
        m_x *= t;
        m_y *= t;
        m_z *= t;
        return *this;
    }

    vec3& operator/=(double t) { return *this *= 1 / t; }

    // define the length of a vector in euclidian distance
    double length() const { return std::hypot(m_x, m_y, m_z); }

    // declare friend binary operator functions

    friend vec3 operator+(const vec3& u, const vec3& v)
    {
        return vec3{u.m_x + v.m_x, u.m_y + v.m_y, u.m_z + v.m_z};
    }

    friend vec3 operator-(const vec3& u, const vec3& v) { return u + (-v); }

    friend vec3 operator*(const vec3& u, const vec3& v)
    {
        return vec3{u.m_x * v.m_x, u.m_y * v.m_y, u.m_z * v.m_z};
    }

    friend vec3 operator*(double t, const vec3& v)
    {
        return vec3{v.m_x * t, v.m_y * t, v.m_z * t};
    }

    friend vec3 operator*(const vec3& v, double t) { return t * v; }

    friend double dot(const vec3& u, const vec3& v)
    {
        return u.m_x * v.m_x + u.m_y * v.m_y + u.m_z * v.m_z;
    }

    friend vec3 operator/(const vec3& v, double t) { return (1 / t) * v; }

    friend vec3 cross(const vec3& u, const vec3& v)
    {
        return vec3{u.m_y * v.m_z - u.m_z * v.m_y,
                    u.m_z * v.m_x - u.m_x * v.m_z,
                    u.m_x * v.m_y - u.m_y * v.m_x};
    }

    friend vec3 unit_vector(const vec3& v) { return v / v.length(); }
};

// Formatter für std::format / std::print / std::println
template <> struct std::formatter<vec3> : std::formatter<double>
{
    // parse() wird von formatter<double> geerbt

    auto format(const vec3& v, std::format_context& ctx) const
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

std::ostream& operator<<(std::ostream& out, const vec3& vec)
{
    return out << std::format("{}", vec);
}

#endif
