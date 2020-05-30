#pragma once

#include "GeneralHeader.h"
#include "ARay.h"
class AMaterial;

struct SHitRecord {
    vec3 p;
    vec3 normal;
    shared_ptr<AMaterial> mat_ptr;
    double t;
    bool front_face;

    inline void set_face_normal(const ARay& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class AHitable {
    public:
        virtual bool Hit(const ARay& r, float t_min, float t_max, SHitRecord& rec) const = 0;
};