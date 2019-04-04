#include "Transform.h"


Transform::Transform() {

}

void
Transform::orthonormalize () {

}

void
Transform::reset() {

}

glm::mat4
Transform::getTransform () const {

}

void
Transform::getTransform (float array[16]) const {

}

Vector3
Transform::getPosition () const {
    return m_position;
}

void
Transform::setPosition(const Vector3& position) {
    m_position = position;
}

void
Transform::setPosition(float x, float y, float z) {
    m_position = Vector3(x,y,z);
}

Vector3
Transform::getRight() const {
    return m_rotScale.getRight();
}

Vector3
Transform::getUp() const {
    return m_rotScale.getUp();
}

Vector3
Transform::getBack() const {
    return m_rotScale.getBack();
}

Matrix3
Transform::getOrientation() const {
    return m_rotScale;
}

void
Transform::setOrientation (const Matrix3& o) {
    m_rotScale = o;
}

void
Transform::setOrientation (const Vector3& r, const Vector3& u, const Vector3& b) {
    m_rotScale = Matrix3(r, u, b);
}

void
Transform::moveRight (float dis) {
    
}

void
Transform::moveUp( float dis) {

}

void
Transform::moveBack (float dis) {

}

void
Transform::moveLocal (float dis, const Vector3& vec) {

}

void
Transform::moveWorld(float dis, const Vector3& loc) {

}

void
Transform::pitch (float angleDegrees) {

}

void
Transform::yaw (float angleDegrees) {

}

void
Transform::roll( float angleDegrees) {

}

void
Transform::rotateLocal(float angleDegrees, const Vector3& axis) {

}

void
Transform::alignWithWorldY () {

}

void
Transform::rotateWorld(float angleDegrees, const Vector3& axis) {

}

void
Transform::scaleLocal (float scale) {
    m_rotScale *= scale;
}

void
Transform::scaleLocal (float x, float y, float z) {
    m_rotScale.setRight(x * m_rotScale.getRight());
    m_rotScale.setUp(   y * m_rotScale.getUp());
    m_rotScale.setBack( z * m_rotScale.getBack());
}

void
Transform::scaleWorld(float scale) {

}

void
Transform::scaleWorld(float x, float y, float z) {

}

void
Transform::shearLocalXByYz(float y, float z) {

}

void
Transform::shearLocalYByXz(float x, float z) {

}

void
Transform::shearLocalZByXy(float x, float y) {

}

void
Transform::invertRt() {
    m_rotScale.invertRotation();
}

void
Transform::combine(const Transform& t) {

}
