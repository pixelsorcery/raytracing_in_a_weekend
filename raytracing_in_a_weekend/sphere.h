#pragma once

#include "hitable.h"
#include "material.h"

template <typename T>
class sphere_t : public hitable_t<T>
{
public:
    sphere_t(vec3_t<T> cen, T r, material<T>* pMat) : center(cen), radius(r), pMat(pMat) {};
    virtual bool hit(const ray_t<T>& r, T tmin, T tmax, hit_record_t<T>& rec) const;
    vec3_t<T> center;
    T radius;
    material<T>* pMat;
};

template <typename T>
bool sphere_t<T>::hit(const ray_t<T>& r, T tmin, T tmax, hit_record_t<T>& rec) const
{
    bool hit = false;
    vec3_t<T> oc = r.origin() - center;
    T a = dot(r.direction(), r.direction());
    T b = dot(oc, r.direction());
    T c = dot(oc, oc) - radius * radius;
    T discriminant = b * b - a * c;
    if (discriminant > 0)
    {
        T temp = (-b - sqrt(discriminant)) / a;
        if (temp < tmax && temp > tmin)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.pMat = pMat;
            hit = true;
            goto exit;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < tmax && temp > tmin)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.pMat = pMat;
            hit = true;
            goto exit;
        }
    }
exit:
    return hit;
}