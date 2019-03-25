#include "Matrix3.h"
#include <cmath>

/**
 *
 * Matrix3.cpp
 * Henry j Schmale
 * Implmentation of Matrix3 Class
 * CSCI 375 - Spring 2019
 */

#define RADIANS(X) (X * M_PI / 180)

Matrix3::Matrix3() 
:   m_right(1.f, 0, 0),
    m_up(0.f, 1.f, 0.f),
    m_back(0.f, 0.f, 1.f) {}

Matrix3::Matrix3(float rx, float ry, float rz,
    float ux, float uy, float uz,
    float bx, float by, float bz)
:   m_right(rx, ry, rz),
    m_up(ux, uy, uz),
    m_back(bx, by, bz) {}

Matrix3::Matrix3(const Vector3& right,
    const Vector3& up,
    const Vector3& back) 
: m_right(right), m_up(up), m_back(back) {}

void
Matrix3::setToIdentity() {
    m_right = Vector3(1.f, 0, 0);
    m_up = Vector3(0.f, 1.f, 0.f);
    m_back = Vector3(0.f, 0.f, 1.f);
}

void 
Matrix3::setToZero() {
    m_right = Vector3();
    m_up = Vector3();
    m_back = Vector3();
}

float*
Matrix3::data() {
    return (float*)this;
}

const float*
Matrix3::data() const {
    return &m_right.x;
}

void
Matrix3::setRight(const Vector3& right) {
    m_right = right;
}

Vector3
Matrix3::getRight () const {
    return m_right;
}

void
Matrix3::setUp (const Vector3& up) {
    m_up = up;
}


Vector3
Matrix3::getUp () const {
    return m_up;
}

void
Matrix3::setBack(const Vector3& back) {
    m_back = back;
}

Vector3
Matrix3::getBack () const {
    return m_back;
}

void
Matrix3::setForward (const Vector3& forward) {
    Vector3 back(forward);
    back.negate();
    m_back = back; 
}

Vector3
Matrix3::getForward() const {
    Vector3 copy(m_back);
    copy.negate();
    return copy;
}

static inline float
det2x2(float a, float b, float c, float d) {
    return a * d - b * c;
}

void
Matrix3::invertRotation() {
}

void
Matrix3::invert () {

}

float
Matrix3::determinant () const {
    float a = m_right.x * det2x2(m_up.y, m_back.y, m_up.z, m_back.z);
    float b = -m_right.y * det2x2(m_up.x, m_back.x, m_up.z, m_back.z);
    float c = m_right.z * det2x2(m_up.x, m_back.x, m_up.y, m_back.y);

    return a + b + c;
}

void
Matrix3::transpose() {
    std::swap(m_right.y, m_up.x);
    std::swap(m_right.z, m_back.x);
    std::swap(m_up.z, m_back.y);
}

void
Matrix3::orthonormalize () {
    m_back.normalize();
    m_right = m_back.cross(m_right);
    m_right.normalize();

    m_up = m_right.cross(m_back);
    m_up.normalize();
}

void
Matrix3::setToScale (float scale) {
    setToScale(scale, scale, scale);
}

void
Matrix3::setToScale (float scaleX, float scaleY, float scaleZ) {
    *this = Matrix3(
            Vector3(scaleX, 0, 0),
            Vector3(0, scaleY, 0),
            Vector3(0, 0, scaleZ));
}


void
Matrix3::setToShearXByYz (float shearY, float shearZ) {
    setToIdentity();
    m_up.x = shearY;
    m_back.x = shearZ;
}


void
Matrix3::setToShearZByXy (float shearX, float shearY) {
    setToIdentity();
    m_right.z = shearX;
    m_up.z = shearY;
}


void
Matrix3::setToRotationX (float angleDegrees) {
    float rad = RADIANS(angleDegrees);
    *this = Matrix3(
            Vector3(1,0,0),
            Vector3(0, cos(rad), -sin(rad)), 
            Vector3(0, sin(rad), cos(rad)));
}

void
Matrix3::setToRotationY (float angleDegrees) {
    float rad = RADIANS(angleDegrees);

    *this = Matrix3(
            Vector3(cos(rad), 0, sin(rad)),
            Vector3(0.f, 1.f, 0.f),
            Vector3(-sin(rad), 0, cos(rad)));
}

void
Matrix3::setToRotationZ (float angleDegrees) {
    float rad = RADIANS(angleDegrees);

    *this = Matrix3(
            Vector3(cos(rad), -sin(rad), 0),
            Vector3(sin(rad), cos(rad), 0),
            Vector3(0, 0, 1.f));
}

void
Matrix3::setFromAngleAxis(float angleDegrees, const Vector3& axis) {
}

void
Matrix3::negate() {
    m_right.negate();
    m_back.negate();
    m_up.negate();
}

Vector3
Matrix3::transform( const Vector3& v) const {
    return Vector3(
           v.dot(Vector3(m_right.x, m_up.x, m_back.x)),
           v.dot(Vector3(m_right.y, m_up.y, m_back.y)),
           v.dot(Vector3(m_right.z, m_up.z, m_back.z)));
}

Matrix3&
Matrix3::operator+= (const Matrix3& m) {
    m_right += m.m_right;
    m_up += m.m_up;
    m_back += m.m_back;
    return *this;
}

Matrix3&
Matrix3::operator-= (const Matrix3& m) {
    m_right -= m.m_right;
    m_up -= m.m_up;
    m_back -= m.m_back; 
    return *this;
}

Matrix3&
Matrix3::operator*= (float scalar) {
    m_right *= scalar;
    m_up *= scalar;
    m_back *= scalar;
    return *this;
}

Matrix3&
Matrix3::operator*= (const Matrix3& m) {
    m_right.x = m_right.dot(Vector3(m.m_right.x, m.m_up.x, m.m_back.x));  
    m_right.y = m_right.dot(Vector3(m.m_right.y, m.m_up.y, m.m_back.y));  
    m_right.z = m_right.dot(Vector3(m.m_right.z, m.m_up.z, m.m_back.z));  
    m_up    = m_up.dot   (Vector3(m.m_right.y, m.m_up.y, m.m_back.y));  
    m_back  = m_back.dot (Vector3(m.m_right.z, m.m_up.z, m.m_back.z));
    return *this;   
}

Matrix3
operator+ (const Matrix3& m1, const Matrix3& m2) {
    Matrix3 res(m1);
    return res += m2;
}

Matrix3
operator- (const Matrix3& m1, const Matrix3& m2) {
    Matrix3 res(m1);
    return res += m2; 
}

// Uniary Negation
Matrix3
operator- (const Matrix3& m) {
    Matrix3 res(m);
    res.negate();
    return res;
}

Matrix3
operator* (float scalar, const Matrix3& m) {
    Matrix3 res(m);
    return res *= scalar;
}

Matrix3
operator* (const Matrix3& m1, const Matrix3& m2) {
    Matrix3 res(m1);
    return res *= m2;
}

Vector3
operator* (const Matrix3& m, const Vector3& v) {
    return m.transform(v);
}

std::ostream&
operator<< (std::ostream& out, const Matrix3& m) {
    out << m.getRight() << "\n"
        << m.getUp() << "\n" 
        << m.getBack();
    return out;
}

bool
operator== (const Matrix3& m1, const Matrix3& m2) {
    return m1.getRight() == m2.getRight() &&
        m1.getUp() == m2.getUp() &&
        m1.getBack() == m2.getBack();
}
