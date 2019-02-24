#include "Vector3.h"
#include <iomanip>
#include <cmath>

/**
 * Vector3.cpp
 * Henry J Schmale
 * Feb 23, 2019
 *
 * Impl of Vector3
 */

const float FLOAT_EQUALITY_TOL = 0.00001f;

Vector3::Vector3() 
:x(0.f), y(0.f), z(0.f) {
}

Vector3::Vector3(float xyz) 
:x (xyz), y(xyz), z(xyz) {
}

Vector3::Vector3(float x, float y, float z) 
:x(x), y(y), z(z) {
}


void
Vector3::set(float xyz) {
    x = y = z = xyz;
}

void 
Vector3::set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void
Vector3::negate() {
    x = -x;
    y = -y;
    z = -z;
}

float 
Vector3::dot(const Vector3& v) const {
    return this->x * v.x + this->y * v.y + this->z * v.z;
}

float 
Vector3::angleBetween(const Vector3& v) const {
    float dot = this->dot(v);
    float len = this->length() * v.length();
    return acos(dot / len);
}

Vector3 
Vector3::cross(const Vector3& v) const {
    return Vector3(
            this->y * v.z - this->z * v.y,
            this->z * v.x - this->x * v.z,
            this->x * v.y - this->y * v.x);
}

float 
Vector3::length() const {
    return sqrt(x * x + y * y + z * z);
}

void 
Vector3::normalize() {
}

Vector3& 
Vector3::operator +=(const Vector3& v) {
}

Vector3& 
Vector3::operator -=(const Vector3& v) {
}

Vector3& 
Vector3::operator *=(float s) {
    x *= s;
    y *= s;
    z *= s;
}

Vector3& 
Vector3::operator /=(float s) {
}

Vector3 
operator +(const Vector3& v1, const Vector3& v2) {
}

Vector3 
operator -(const Vector3& v1, const Vector3& v2) {
}

Vector3 
operator -(const Vector3& v) {
    Vector3 a(v);
    a.negate();
    return a;
}

Vector3 
operator *(float s, const Vector3& v) {
}

Vector3 
operator *(const Vector3& v, float s) {
}

Vector3 
operator /(const Vector3& v, float s) {
}

std::ostream& 
operator <<(std::ostream& out, const Vector3& v) {
    out << std::setw(10) 
        << std::setprecision(2) 
        << v.x  
        << std::setw(10) 
        << std::setprecision(2) 
        << v.y
        << std::setw(10) 
        << std::setprecision(2) 
        << v.z;
}

inline bool
float_fuzzy_equals(float a, float b) {
    return fabs(a - b) <= FLOAT_EQUALITY_TOL;
}

bool 
operator ==(const Vector3& v1, const Vector3& v2) {
    return float_fuzzy_equals(v1.x, v2.x) &&
       float_fuzzy_equals(v1.y, v2.y) &&
       float_fuzzy_equals(v1.z, v2.z); 
}
