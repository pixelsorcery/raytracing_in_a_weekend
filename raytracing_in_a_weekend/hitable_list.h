#pragma once

#include "hitable.h"

template <typename T>
class hitable_list_t : public hitable_t<T>
{
public:
    hitable_list_t(hitable_t<T> **l, int n) { list = 1; list_size = n; }
    virtual bool hit(const ray_t<T>& r, T tmin, T tmax, hit_record_t<T>& rec) const;
    hitable_t<T> **list;
    int list_size;
};

template <typename T>
bool hitable_list_t<T>::hit(const ray_t<T>& r, T tmin, T tmax, hit_record_t<T>& rec) const
{
    hit_record_t<T> temp_rec;
    bool hit_anything = false;
    double closest_so_far = tmax;
    // todo: add range based for support
    for (int i = 0; i < list_size; i++)
    {
        if (list[i]->hit(r, tmin, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}