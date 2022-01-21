#pragma once

#include <iostream>
#include <cmath>

class Vec3;

inline std::istream& operator>>(std::istream &is, Vec3 &t);
inline std::ostream& operator<<(std::ostream &os, const Vec3 &t);
inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2);
inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2);
inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2);
inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2);
inline Vec3 operator*(double t, const Vec3 &v);
inline Vec3 operator/(Vec3 v, double t);
inline Vec3 operator*(const Vec3 &v, double t);
inline Vec3 cross(const Vec3 &v1, const Vec3 &v2);

class Vec3 
{
    public:
        Vec3() {}
        Vec3(double e0, double e1, double e2) { e[0] = e0; e[1] = e1; e[2] = e2; }

        inline double x() const { return e[0]; }
        inline double y() const { return e[1]; }
        inline double z() const { return e[2]; }
        inline double r() const { return e[0]; }
        inline double g() const { return e[1]; }
        inline double b() const { return e[2]; }

        inline const Vec3& operator+() const { return *this; }
        inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
        inline double operator[](int i) const { return e[i]; }
        inline double& operator[](int i) { return e[i]; }

        inline Vec3& operator+=(const Vec3 &v2);
        inline Vec3& operator-=(const Vec3 &v2);
        inline Vec3& operator*=(const Vec3 &v2);
        inline Vec3& operator/=(const Vec3 &v2);
        inline Vec3& operator*=(const double t);
        inline Vec3& operator/=(const double t);

        Vec3 square_root(const Vec3 &v) { return Vec3(std:: sqrt(v.e[0]), sqrt(v.e[1]), sqrt(v.e[2])); }

        double length() const { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
        double squared_length() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
        Vec3 unit_vector() const { return *this / this->length(); }
        bool is_null_vector() const { return e[0] == 0. && e[1] == 0. && e[2] == 0.; }
        bool near_zero() const { return (fabs(e[0]) < 1e-8) && (fabs(e[1]) < 1e-8) && (fabs(e[2]) < 1e-8); }
        double dot(const Vec3 &v) const { return this->e[0] * v[0] + this->e[1] * v[1] + this->e[2] * v[2]; }
        Vec3 reflect_on(const Vec3 &v) const { return *this - 2 * this->dot(v) * v; }
        double angle_with(const Vec3 &v) const { return asin(this->dot(v) / (this->length() * v.length())); }

        double e[3];
};


inline std::istream& operator>>(std::istream &is, Vec3 &t) {
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const Vec3 &t) {
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vec3 operator/(Vec3 v, double t) {
    return Vec3(v.e[0]/t, v.e[1]/t, v.e[2]/t);
}

inline Vec3 operator*(const Vec3 &v, double t) {
    return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vec3 cross(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
                v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
                v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

inline Vec3& Vec3::operator+=(const Vec3 &v){
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

inline Vec3& Vec3::operator*=(const Vec3 &v){
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

inline Vec3& Vec3::operator/=(const Vec3 &v){
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

inline Vec3& Vec3::operator-=(const Vec3& v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

inline Vec3& Vec3::operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline Vec3& Vec3::operator/=(const double t) {
    double k = 1.0f/t;

    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
    return *this;
}
