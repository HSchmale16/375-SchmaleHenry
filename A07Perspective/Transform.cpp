#include "Transform.h"
#include <glm/gtc/type_ptr.hpp>

/**
 * Transform.cpp
 * Impl of transform class for graphics
 * Henry J Schmale
 * CSCI 375
 * Spring 2019
 */


Transform::Transform() {}

void
Transform::orthonormalize () {
    m_rotScale.orthonormalize();
}

void
Transform::reset() {
    m_rotScale.setToIdentity();
    m_position = Vector3();
}

Matrix4
Transform::getTransform () const {
    // float data[16];
    // getTransform(data);
    
    return Matrix4(
        Vector4(
            m_rotScale.getRight().x,
            m_rotScale.getRight().y,
            m_rotScale.getRight().z,
            0.f
        ),
        Vector4(
            m_rotScale.getUp().x,
            m_rotScale.getUp().y,
            m_rotScale.getUp().z,
            0.f
        ),
        Vector4(
            m_rotScale.getBack().x,
            m_rotScale.getBack().y,
            m_rotScale.getBack().z,
            0.f
        ),
        Vector4(
            m_position.x,
            m_position.y,
            m_position.z,
            1.f
        )
    );
}

void
Transform::getTransform (float array[16]) const {
    array[ 0] = m_rotScale.getRight().x;
    array[ 1] = m_rotScale.getRight().y;
    array[ 2] = m_rotScale.getRight().z;
    array[ 3] = 0;

    array[ 4] = m_rotScale.getUp().x;
    array[ 5] = m_rotScale.getUp().y;
    array[ 6] = m_rotScale.getUp().z;
    array[ 7] = 0;

    array[ 8] = m_rotScale.getBack().x;
    array[ 9] = m_rotScale.getBack().y;
    array[10] = m_rotScale.getBack().z;
    array[11] = 0;

    array[12] = m_position.x;
    array[13] = m_position.y;
    array[14] = m_position.z;
    array[15] = 1;
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
    Vector3 myvec = m_rotScale.getRight();
    m_position += myvec * dis;
}

void
Transform::moveUp( float dis) {
    Vector3 myvec = m_rotScale.getUp();
    m_position += myvec * dis;
}

void
Transform::moveBack (float dis) {
    Vector3 myvec = m_rotScale.getBack();
    m_position += myvec * dis;
}

void
Transform::moveLocal (float dis, const Vector3& vec) {
    Matrix3 orient(m_rotScale);
    orient.orthonormalize();

    moveRight(vec.x);
    moveUp(vec.y);
    moveBack(vec.z);
}

void
Transform::moveWorld(float dis, const Vector3& loc) {
    m_position += dis * loc;
}

void
Transform::pitch (float angleDegrees) {
    Matrix3 rot;
    rot.setToRotationX(angleDegrees);
    m_rotScale *= rot;
}

void
Transform::yaw (float angleDegrees) {
    Matrix3 rot;
    rot.setToRotationY(angleDegrees);
    m_rotScale *= rot;
}

void
Transform::roll( float angleDegrees) {
    Matrix3 rot;
    rot.setToRotationZ(angleDegrees);
    m_rotScale *= rot;
}

void
Transform::rotateLocal(float angleDegrees, const Vector3& axis) {
    Matrix3 rotate;
    rotate.setFromAngleAxis(angleDegrees, axis);

    m_rotScale *= rotate;
}

void
Transform::alignWithWorldY () {
    Vector3 up = Vector3(0, 1, 0);
    m_rotScale.setUp(up);
    Vector3 right = m_rotScale.getBack().cross(m_rotScale.getUp());
    Vector3 back  = m_rotScale.getRight().cross(m_rotScale.getUp());
    right = back.cross(up);
    
    right.normalize();
    back.normalize();

    if (back == Vector3(0, 1, 0) || back == Vector3(0, -1, 0)) {
        back = Vector3(0, 0, 1);
        right = up.cross(back); 
    }
    m_rotScale.setRight(right);
    m_rotScale.setBack(back);
}

void
Transform::rotateWorld(float angleDegrees, const Vector3& axis) {
    Matrix3 rot;
    rot.setFromAngleAxis(angleDegrees, axis);
    m_rotScale = rot * m_rotScale;

    m_position = rot.transform(m_position);
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
    Matrix3 s;
    s.setToScale(scale);

    m_rotScale *= scale;
    m_position *= scale;
}

void
Transform::scaleWorld(float x, float y, float z) {
    Matrix3 scale;
    scale.setToScale(x, y, z);

    m_rotScale = scale * m_rotScale; 
    m_position.x *= x;
    m_position.y *= y;
    m_position.z *= z;
}

void
Transform::shearLocalXByYz(float y, float z) {
    Matrix3 shear;
    shear.setToShearXByYz(y, z);

    m_rotScale *= shear;
}

void
Transform::shearLocalYByXz(float x, float z) {
    Matrix3 shear;
    shear.setToShearYByXz(x, z);

    m_rotScale *= shear;
}

void
Transform::shearLocalZByXy(float x, float y) {
    Matrix3 shear;
    shear.setToShearZByXy(x, y);

    m_rotScale *= shear;
}

void
Transform::invertRt() {
    m_rotScale.invertRotation();
    m_position.negate();
    m_position = m_rotScale.transform(m_position);
}

void
Transform::combine(const Transform& t) {
    m_position = m_position + m_rotScale * t.getPosition();
    m_rotScale *= t.getOrientation();
}

std::ostream&
operator<< (std::ostream& out, const Transform& t) {
    Matrix3 mat(t.getOrientation());
    Vector3 pos(t.getPosition());

    out << mat.getRight().x << mat.getUp().x << mat.getBack().x << pos.x << '\n'
        << mat.getRight().y << mat.getUp().y << mat.getBack().y << pos.y << '\n'
        << mat.getRight().z << mat.getUp().z << mat.getBack().z << pos.z << '\n'
        << 0.f << 0.f << 0.f << 1.f << '\n';

    return out;
}

bool
operator== (const Transform& t1, const Transform& t2) {
    return t1.getOrientation() == t2.getOrientation() &&
        t1.getPosition() == t2.getPosition();
}
