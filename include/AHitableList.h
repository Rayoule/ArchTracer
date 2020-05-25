#pragma once

#include "AHitable.h"

class AHitableList: public AHitable {

public:
    AHitableList() {}
    AHitableList(AHitable **l, int n) { list = l; list_size = n; }
    virtual bool Hit(const ARay& r, float t_min, float t_max, SHitRecord& rec) const;
    AHitable **list;
    int list_size;

};

bool AHitableList::Hit(const ARay& r, float t_min, float t_max, SHitRecord& rec) const {

    SHitRecord temp_rec;
    bool bHitAnything = false;
    double closest_so_far = t_max;

    for (int i = 0; i < list_size; i++) {
        if (list[i]->Hit(r, t_min, closest_so_far, temp_rec)) {
            bHitAnything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return bHitAnything;
}