#pragma once

#include "AHitable.h"
#include "Vec3.h"

class ASphere: public AHitable {
    public:
        ASphere() {}
        ASphere(vec3 cen, double r, shared_ptr<AMaterial> m)
            : center(cen), radius(r), mat_ptr(m) {};

        virtual bool Hit(const ARay& r, float tmin, float tmax, SHitRecord& rec) const;

    public:
        vec3 center;
        float radius;
        shared_ptr<AMaterial> mat_ptr;
};

bool ASphere::Hit(const ARay& r, float t_min, float t_max, SHitRecord& rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().squared_length();
    auto half_b = dot(oc, r.direction());
    auto c = oc.squared_length() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if (discriminant > 0) {
        auto root = sqrt(discriminant);
        auto temp = (-half_b - root)/a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-half_b + root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}