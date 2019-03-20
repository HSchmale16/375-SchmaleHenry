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

Vector3
Matrix3::getForward() const {
    Vector3 copy(m_back);
    copy.negate();
    return copy;
}

void
Matrix3::invertRotation() {

}

void
Matrix3::invert () {

}

float
Matrix3::determinant () const {
    float minar1 = m_up.y * m_back.z - m_up.z * m_back.y;
    float minar2 = (m_right.y * m_up.z - m_right.z * m_up.y) * -1;
    return 0.f; 
}

void
Matrix3::transpose() {

}

void
Matrix3::orthonormalize () {
    
}

void
Matrix3::setToScale (float scale) {

}

void
Matrix3::setToScale (float scaleX, float scaleY, float scaleZ) {

}

void
Matrix3::setToShearXByYz (float shearY, float shearZ) {

}

void
Matrix3::setToShearXByYz (float shearX, float shearZ) {
}


void
Matrix3::setToShearZByXy (float shearX, float shearY) {

}


void
Matrix3::setToRotationX (float angleDegrees) {

}

void
Matrix3::setToRotationY (float angleDegrees) {

}

void
Matrix3::setToRotationZ (float angleDegrees) {

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

}

Matrix3&
operator+= (const Matrix3& m) {

}

Matrix3&
operator-= (const Matrix3& m) {

}

Matrix3&
operator*= (float scalar) {

}

Matrix3&
operator*= (const Matrix3& m) {

}

Matrix3
operator+ (const Matrix3& m1, const Matrix3& m2) {

}

Matrix3
operator- (const Matrix3& m1, const Matrix3& m2) {
    
}

Matrix3
operator- (const Matrix3& m) {

}

Matrix3
operator* (float scalar, const Matrix3& m) {

}

Matrix3
operator* (const Matrix3& m1, const Matrix3& m2) {

}

Vector3
operator* (const Matrix3& m, const Vector3& v) {

}

std::ostream&
operator<< (std::ostream& out, const Matrix3& m) {

}

bool
operator== (const Matrix3& m1, const Matrix3& m2) {
    return m1.getRight() == m2.getRight() &&
        m1.getUp() == m2.getUp() &&
        m1.getBack() == m2.getBack();
}
