#pragma once

#include "ray.h"
#include "hitable.h"

extern vec3_t<float> random_in_unit_sphere();

template <typename T>
class material
{
public:
    virtual bool scatter(const ray_t<T>& r_in, const hit_record_t<T>& rec, vec3_t<T>& attenuation, ray_t<T>& scattered) const = 0;
};

template <typename T>
class lambertian : public material<T>
{
public:
    lambertian(const vec3_t<T>& a) : albedo(a) {}
    virtual bool scatter(const ray_t<T>& r_in, const hit_record_t<T>& rec, vec3_t<T>& attenuation, ray_t<T>& scattered) const
    {
        vec3_t<T> target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray_t<T>(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }
    vec3_t<T> albedo;
};

template <typename T>
class metal : public material<T>
{
public:
    metal(const vec3_t<T>& a) : albedo(a) {}
    virtual bool scatter(const ray_t<T>& r_in, const hit_record_t<T>& rec, vec3_t<T>& attenuation, ray_t<T>& scattered) const
    {
        vec3_t<T> reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray_t<T>(rec.p, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
    vec3_t<T> albedo;
};

