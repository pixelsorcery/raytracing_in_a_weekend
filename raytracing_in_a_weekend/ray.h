#pragma once
#include "vec3.h"

template <typename T>
class ray_t
{
public:
    ray_t() {};
    ray_t(const vec3_t<T>& a, const vec3_t<T>& b) { A = a; B = b; }
    vec3_t<T> origin() const { return A; }
    vec3_t<T> direction() const { return B; }
    vec3_t<T> point_at_parameter(float t) const { return A + t * B; }

    vec3_t<T> A;
    vec3_t<T> B;
};