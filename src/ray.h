#ifndef RAY_H
#define RAY_H

#include "color.h"
#include "point3.h"
#include "vec3.h"

class ray
{
  private:
    point3 m_origin;
    vec3 m_direction;

  public:
    ray() {}

    ray(const point3& origin, const vec3& direction)
        : m_origin{origin}, m_direction{direction}
    {
    }

    const point3& getOrigin() const { return m_origin; }
    const vec3& getDirection() const { return m_direction; }

    point3 at(double t) const { return m_origin + t * m_direction; }

    // in this function we implement a sky coloring by linearly blend white to
    // blue depending on thi height (y coordinate)
    friend color ray_color(const ray& r)
    {
        // the y value (vertical direction) is in the range [-1,1] after
        // normalizing
        vec3 unit_direction = unit_vector(r.getDirection());

        // now we remap to the intervall [0,1]
        double a = 0.5 * (unit_direction.get_y() + 1.0);

        return color{(1.0 - a) * color{1.0, 1.0, 1.0} +
                     a * color{0.5, 0.7, 1.0}};
    }
};

double hit_sphere(const point3& center, double radius, const ray& r)
{
    vec3 oc = center - r.getOrigin();
    double a = r.getDirection().length_squared();
    double h = dot(r.getDirection(), oc);
    double c = oc.length_squared() - radius * radius;
    double discriminate = h * h - a * c;
    if (discriminate < 0)
    {
        return -1.0;
    }
    else
    {
        return (h - std::sqrt(discriminate)) / a;
    }
}

#endif
