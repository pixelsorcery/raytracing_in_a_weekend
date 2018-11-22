#pragma once

#include "ray.h"

extern const int32_t WIDTH;
extern const int32_t HEIGHT;

template <typename T>
class camera_t
{
public:
    camera_t() : lower_left_corner(vec3_t<T>(-WIDTH / 2.0f, -HEIGHT / 2.0f, -HEIGHT / 2.0f)),
                 horizontal(vec3_t<T>(WIDTH, 0.0f, 0.0f)),
                 vertical(vec3_t<T>(0.0f, HEIGHT, 0.0f)),
                 origin(vec3_t<T>(0.0f, 0.0f, 0.0f)) { }

    ray_t<T> get_ray(T u, T v)
    {
        return ray_t<T>(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }


    vec3_t<T> origin;
    vec3_t<T> lower_left_corner;
    vec3_t<T> horizontal;
    vec3_t<T> vertical;
};