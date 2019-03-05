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
