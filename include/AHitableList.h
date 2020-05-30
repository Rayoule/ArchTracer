#pragma once

#include "AHitable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class AHitableList: public AHitable {
    public:
        AHitableList() {}
        AHitableList(shared_ptr<AHitable> object) { add(object); }

        void clear() { objects.clear(); }
        void add(shared_ptr<AHitable> object) { objects.push_back(object); }

        virtual bool Hit(const ARay& r, float tmin, float tmax, SHitRecord& rec) const;

    public:
        std::vector<shared_ptr<AHitable>> objects;
};

bool AHitableList::Hit(const ARay& r, float t_min, float t_max, SHitRecord& rec) const {
    SHitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->Hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}