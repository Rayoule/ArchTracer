#pragma once

#include "ARay.h"

class ACamera {

public:

    ACamera() {
        low_left_corner = vec3(-2.0, -1.0, -1.0);
        horizontal = vec3(4.0, 0.0, 0.0);
        vertical = vec3(0.0, 2.0, 0.0);
        origin = vec3(0.0, 0.0, 0.0);
    }

    ARay GetRay(float u, float v) {
        return ARay(origin, low_left_corner + u*horizontal + v*vertical);
    }

    vec3 low_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 origin;
};