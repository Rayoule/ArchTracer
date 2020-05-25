#pragma once

#include "ARay.h"

struct SHitRecord {
    float t;
    vec3 p;
    vec3 normal;
};

class AHitable {

public:

    virtual bool Hit(const ARay& r, float t_min, float t_max, SHitRecord& rec) const = 0;
};