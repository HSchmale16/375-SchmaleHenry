#include "Matrix4.h"
#include <cmath>

#define RADIANS(X) (X * M_PI / 180)

/**
 * Matrix4.cpp
 * Henry J Schmale
 * April 10, 2019
 *
 * Impl of Matrix4
 *
 */

Matrix4::Matrix4 () 
: m_right(1, 0, 0, 0), m_up(0,1,0,0), 
  m_back(0,0,1,0), m_translation(0,0,0,1) {}

Matrix4::Matrix4(const Vector4& right, const Vector4& up,
        const Vector4& back, const Vector4& translation)
: m_right(right), m_up(up), m_back(back), m_translation(translation)
{}

Vector4
Matrix4::getRight() const {
    return m_right;
}

Vector4
Matrix4::getUp() const {
    return m_up;
}

Vector4
Matrix4::getBack () const {
    return m_back;
}

Vector4
Matrix4::getTranslation () const {
    return m_translation;
}

void
Matrix4::setToIdentity () {
    *this = Matrix4();
}

void
Matrix4::setToZero() {
    m_right = Vector4();
    m_up = Vector4();
    m_back = Vector4();
    m_translation = Vector4();
}

const float*
Matrix4::data() const {
    return &m_right.x;
}

void
Matrix4::setToPerspectiveProjection(double fovYDegrees, double aspectRatio,
        double nearPlaneZ, double farPlaneZ) {
    this->setToZero();

    float tanfov2 = tan(RADIANS(fovYDegrees) / 2.f);
    float nmf = nearPlaneZ - farPlaneZ;

    m_right.x = 1.f / (aspectRatio * tanfov2);
    m_up.y = 1.f / tanfov2;
    m_back.z = (nearPlaneZ + farPlaneZ) / nmf; 
    m_back.w = -1.f;
    m_translation.z = (2 * nearPlaneZ * farPlaneZ) / nmf; 
}

// l left
// r right
// b bottom
// t top
// n near clip plane
// f far clip plane
void
Matrix4::setToPerspectiveProjection(double left, double right,
        double bottom, double top,
        double nearPlaneZ, double farPlaneZ) {
    this->setToZero();
    
    float n2 = 2 * nearPlaneZ;

    m_right.x = n2 / (right - left);
    m_up.y = n2 / (top - bottom);
    m_back.x = (right + left) / (right - left);
    m_back.y = (top + bottom) / (top - bottom);
    m_back.z = (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ);
    m_back.w = -1.f;
    m_translation.z = (n2 * farPlaneZ) / (nearPlaneZ - farPlaneZ);
}

void
Matrix4::setToOrthographicProjection (double left, double right,
        double bottom, double top,
        double nearPlaneZ, double farPlaneZ) {
    this->setToZero();

    m_right.x = 2.f / (right - left);
    m_up.y = 2.f / (top - bottom);
    m_back.z = 2.f / (nearPlaneZ - farPlaneZ);
    m_translation.x = - (right + left) / (right - left);
    m_translation.y = - (top + bottom) / (top - bottom);
    m_translation.z = (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ);
    m_translation.w = 1.f;
}

std::ostream&
operator<< (std::ostream& out, const Matrix4& m) {
    Vector4 r = m.getRight();
    Vector4 u = m.getUp();
    Vector4 b = m.getBack();
    Vector4 t = m.getTranslation();

    out << r.x << u.x << b.x << t.x << "\n"
        << r.y << u.y << b.y << t.y << "\n"
        << r.z << u.z << b.z << t.z << "\n"
        << r.w << u.w << b.w << t.w << "\n";

    return out;
}

bool
operator== (const Matrix4& m1, const Matrix4& m2) {
    return m1.getRight() == m2.getRight() &&
        m1.getUp() == m2.getUp() &&
        m1.getBack() == m2.getBack() &&
        m1.getTranslation() == m2.getTranslation();
}
