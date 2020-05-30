#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>


// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const float infinity = std::numeric_limits<float>::infinity();
const float pi = float(3.1415926535897932385);

// Utility Functions

inline float degrees_to_radians(float degrees) {
    return degrees * pi / 180;
}

inline float clamp(float x, float min, float max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline float random_float() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline float random_float(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_float();
}

// Common Headers

#include "ARay.h"
#include "Vec3.h"