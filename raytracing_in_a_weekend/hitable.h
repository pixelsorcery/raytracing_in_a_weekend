#pragma once

#include "ray.h"

template <typename T>
struct hit_record_t
{
    T t;
    vec3_t<T> p;
    vec3_t<T> normal;
};

template <typename T>
class hitable_t
{
public:
    virtual bool hit(const ray_t<T>& r, T tmin, T tmax, hit_record_t<T>& rec) const = 0;
};