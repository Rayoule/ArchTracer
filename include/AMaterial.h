#pragma once

#include "AHitable.h"

class AMaterial {

    public:
        virtual bool Scatter(const ARay& r_in, const SHitRecord& rec, vec3& attenuation, ARay& scattered) const = 0;
};



class lambertian : public AMaterial {
    public:
        lambertian(const vec3& a) : albedo(a) {}

        virtual bool Scatter(
            const ARay& r_in, const SHitRecord& rec, vec3& attenuation, ARay& scattered
        ) const {
            vec3 scatter_direction = rec.normal + Random_in_unit_sphere();
            scattered = ARay(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }

    public:
        vec3 albedo;
};



class AMetal : public AMaterial {
    public:
        AMetal(const vec3& a, float f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        virtual bool Scatter(
            const ARay& r_in, const SHitRecord& rec, vec3& attenuation, ARay& scattered
        ) const {
            vec3 reflected = Reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = ARay(rec.p, reflected + fuzz*Random_in_unit_sphere());
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }

    public:
        vec3 albedo;
        float fuzz;
};