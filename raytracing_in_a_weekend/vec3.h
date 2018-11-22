#pragma once
#include <cmath>
#include <iostream>

template <typename T>
class vec3_t
{
public:
    vec3_t() {}
    vec3_t(T e0, T e1, T e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
    inline T x() const { return e[0]; }
    inline T y() const { return e[1]; }
    inline T z() const { return e[2]; }
    inline T r() const { return e[0]; }
    inline T g() const { return e[1]; }
    inline T b() const { return e[2]; }

    inline const vec3_t& operator+() const { return *this; }
    inline vec3_t operator-() const { return vec3_t(-e[0], -e[1], -e[2]); }
    inline T operator[](int i) const { return e[i]; }
    inline T& operator[](int i) { return e[i]; }

    inline vec3_t& operator+=(const vec3_t& v2);
    inline vec3_t& operator-=(const vec3_t& v2);
    inline vec3_t& operator*=(const vec3_t& v2);
    inline vec3_t& operator/=(const vec3_t& v2);
    inline vec3_t& operator*=(const T t);
    inline vec3_t& operator/=(const T t);

    inline float length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);}
    inline float squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
    inline void make_unit_vector();

    T e[3];
};

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
