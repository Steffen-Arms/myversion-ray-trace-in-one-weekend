#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{

  private:
    point3 m_center;
    double m_radius;
    shared_ptr<material> m_mat;

  public:
    sphere(const point3& center, double radius, shared_ptr<material> mat)
        : m_center(center), m_radius(std::fmax(0, radius)), m_mat{mat}
    {
        // TODO: Initialize the material pointer `mat`.
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override
    {
        vec3 oc = m_center - r.getOrigin();
        auto a = r.getDirection().length_squared();
        auto h = dot(r.getDirection(), oc);
        auto c = oc.length_squared() - m_radius * m_radius;

        auto discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;
        if (!ray_t.surrounds(root))
        {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - m_center) / m_radius;
        rec.set_face_normal(r, outward_normal);
        // rec.normal = (rec.p - m_center) / m_radius;
        rec.mat = m_mat;

        return true;
    }
};

#endif
