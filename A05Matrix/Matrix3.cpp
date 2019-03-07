#include "Matrix3.h"

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
    return &m_right.x;
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







