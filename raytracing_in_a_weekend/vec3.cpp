#include <cmath>
#include <iostream>
#include "vec3.h"

template<typename T>
inline std::istream& operator>>(std::istream &is, vec3_t<T> &t)
{
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

template<typename T>
inline std::istream& operator<<(std::istream &os, vec3_t<T> &t)
{
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

template<typename T>
inline void vec3_t<T>::make_unit_vector()
{
    T k = static_cast<T>(1.0) / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    e[0] *= k; e[1] *= k; e[2] *= k;
}

template<typename T>
inline vec3_t<T> operator+(const vec3_t<T>& v1, const vec3_t<T>& v2)
{
    return vec3_t<T>(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

template<typename T>
inline vec3_t<T> operator-(const vec3_t<T>& v1, const vec3_t<T>& v2)
{
    return vec3_t<T>(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

template<typename T>
inline vec3_t<T> operator*(const vec3_t<T>& v1, const vec3_t<T>& v2)
{
    return vec3_t<T>(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

template<typename T>
inline vec3_t<T> operator/(const vec3_t<T>& v1, const vec3_t<T>& v2)
{
    return vec3_t<T>(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

template<typename T>
inline vec3_t<T> operator*(const vec3_t<T>& v, const T t)
{
    return vec3_t<T>(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

template<typename T>
inline vec3_t<T> operator*(const T t, const vec3_t<T>& v)
{
    return vec3_t<T>(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

template<typename T>
inline vec3_t<T> operator/(const vec3_t<T>& v, const T t)
{
    return vec3_t<T>(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

template<typename T>
inline T dot(const vec3_t<T>& v1, const vec3_t<T>& v2)
{
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

template<typename T>
inline vec3_t<T> cross(const vec3_t<T>& v1, const vec3_t<T>& v2)
{
    return vec3_t<T>((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
                    -(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
                     (v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}

template<typename T>
inline vec3_t<T>& vec3_t<T>::operator+=(const vec3_t& v2)
{
    e[0] += v2.e[0];
    e[1] += v2.e[1];
    e[2] += v2.e[2];
    return *this;
}

template<typename T>
inline vec3_t<T>& vec3_t<T>::operator-=(const vec3_t& v2)
{
    e[0] -= v2.e[0];
    e[1] -= v2.e[1];
    e[2] -= v2.e[2];
    return *this;
}

template<typename T>
inline vec3_t<T>& vec3_t<T>::operator*=(const vec3_t& v2)
{
    e[0] *= v2.e[0];
    e[1] *= v2.e[1];
    e[2] *= v2.e[2];
    return *this;
}

template<typename T>
inline vec3_t<T>& vec3_t<T>::operator/=(const vec3_t& v2)
{
    e[0] /= v2.e[0];
    e[1] /= v2.e[1];
    e[2] /= v2.e[2];
    return *this;
}

template<typename T>
inline vec3_t<T>& vec3_t<T>::operator*=(const T t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

template<typename T>
inline vec3_t<T>& vec3_t<T>::operator/=(const T t)
{
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;
    return *this;
}

template<typename T>
inline vec3_t<T> unit_vector(vec3_t<T> v)
{
    return v / v.length();
}
