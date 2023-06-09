/**
 * Camera.cpp
 * The implementation of my camera class as per the directions
 *
 * Henry J Schmale
 * Feb 26, 2019
 * 
 */

#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <cstdio>

void 
print_vec(const Vector3& v) {
    printf("%f %f %f\n", v.x, v.y, v.z);
}

Camera::Camera() {}

Camera::Camera(const Vector3& eyePoint, const Vector3& localBackDirection,
    float nearClipPlaneDistance, float farClipPlaneDistance,
    float aspectRatio, float verticalFieldOfViewDegrees)
: m_nearClipPlaneDistance(nearClipPlaneDistance),
  m_farClipPlaneDistance(farClipPlaneDistance), m_aspectRatio(aspectRatio), 
  m_verticalFieldOfViewDegrees(verticalFieldOfViewDegrees),
  m_currentYaw(0),
  m_initEyePoint(eyePoint),
  m_initBackwardsPoint(localBackDirection)
{
    m_projectionMat = glm::perspective(
        glm::radians(m_verticalFieldOfViewDegrees),
        m_aspectRatio,
        m_nearClipPlaneDistance,
        m_farClipPlaneDistance);
    
    // use a guess for the initial up vector
    Vector3 up = Vector3(0.f, 1.0f, 0.f);
    Vector3 right = localBackDirection.cross(up);
    up = localBackDirection.cross(right);

    m_world.setOrientation(Matrix3(right, up, localBackDirection));
    m_world.setPosition(eyePoint);
}



void
Camera::setProjection (float verticalFovDegrees, float aspectRatio, float nearZ, float farZ)
{
    m_verticalFieldOfViewDegrees = verticalFovDegrees;
    m_aspectRatio = aspectRatio;
    m_nearClipPlaneDistance = nearZ;
    m_farClipPlaneDistance = farZ;
    m_projectionMat = glm::perspective(
        glm::radians(m_verticalFieldOfViewDegrees),
        m_aspectRatio,
        m_nearClipPlaneDistance,
        m_farClipPlaneDistance);
}

glm::mat4
Camera::getProjectionMatrix() const 
{
    return m_projectionMat;
}

Transform
Camera::getViewMatrix() {
    Vector3 eye = m_world.getPosition();
    Vector3 at = eye - m_world.getOrientation().getBack();

    Vector3 back = m_world.getPosition() - at;
    back.normalize();

    Vector3 right = Vector3(0, 1, 0).cross(back);
    right.normalize();

    Vector3 up = back.cross(right);

    Transform view;
    view.setOrientation(Matrix3(right, up, back));
    view.setPosition(Vector3(
                -eye.dot(right),
                -eye.dot(up),
                -eye.dot(back)));
    return view;
}

void
Camera::moveUp(float distance) {
    m_world.moveUp(distance);
}

void
Camera::moveRight(float distance) {
    m_world.moveRight(distance);
}

void
Camera::moveBack(float distance) {
    m_world.moveBack(distance);
}

void
Camera::setPosition(const Vector3& position) {
    m_world.setPosition(position);
}

void
Camera::yaw(float degrees) {
    m_world.yaw(degrees);
}

void
Camera::roll(float degrees) {
    m_world.roll(degrees);
}

void
Camera::pitch(float degrees) {
    m_world.pitch(degrees);
}

void
Camera::reset() {
    Vector3 m_up = Vector3(0.f, 1.0f, 0.f);

    Vector3 m_right = m_initBackwardsPoint.cross(m_up);
    m_up = m_initBackwardsPoint.cross(m_right);

    m_world.setOrientation(Matrix3(m_right, m_up, m_initBackwardsPoint)); 
    m_world.setPosition(m_initEyePoint);
}
