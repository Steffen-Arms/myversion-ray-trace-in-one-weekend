# 0 "/home/popcorn/project_programmer/programming/myproject-ray-tracing/src/vec3.cppm"
# 1 "/home/popcorn/project_programmer/programming/myproject-ray-tracing/build//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3
# 0 "<command-line>" 2
# 1 "/home/popcorn/project_programmer/programming/myproject-ray-tracing/src/vec3.cppm"
export module vec3;
import std;

export struct Vec3
{
    double x{}, y{}, z{};

    Vec3 operator+(const Vec3& o) const { return {x + o.x, y + o.y, z + o.z}; }
    Vec3 operator*(double s) const { return {x * s, y * s, z * s}; }
    double length() const { return std::sqrt(x * x + y * y + z * z); }
};
