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
: m_eyePoint(eyePoint), // m_backwardsPoint(localBackDirection), 
  m_nearClipPlaneDistance(nearClipPlaneDistance),
  m_farClipPlaneDistance(farClipPlaneDistance), m_aspectRatio(aspectRatio), 
  m_verticalFieldOfViewDegrees(verticalFieldOfViewDegrees),
  m_currentYaw(0),
  m_initEyePoint(m_eyePoint),
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

    m_directions = Matrix3(right, up, localBackDirection);

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

glm::mat4
Camera::getViewMatrix() 
{
    if (m_dirty) {
        Vector3 at = m_eyePoint - m_directions.getBack();
        print_vec(at);
      
        const Vector3 m_up = m_directions.getUp(); 
        
        glm::vec3 up(m_up.x, m_up.y, m_up.z);
        glm::vec3 vat(at.x, at.y, at.z);
        glm::vec3 eye(m_eyePoint.x, m_eyePoint.y, m_eyePoint.z);

        m_viewMat = glm::lookAt(eye, vat, up);
        m_dirty = false;
    }
    return m_viewMat;
}

void
Camera::moveUp(float distance) {
    this->m_eyePoint += m_directions.getUp() * distance;
    m_dirty = true;
}

void
Camera::moveRight(float distance) {
    this->m_eyePoint += m_directions.getRight() * distance;
    m_dirty = true;
}

void
Camera::moveBack(float distance) {
    this->m_eyePoint += m_directions.getBack() * distance;
    m_dirty = true;
}

void
Camera::setPosition(const Vector3& position) {
    m_eyePoint = position;
    m_dirty = true;
}

void
Camera::yaw(float degrees) {
    m_dirty = true;
    
    Matrix3 rot;
    rot.setToRotationY(degrees);
    m_directions *= rot;
}

void
Camera::roll(float degrees) {
    m_dirty = true;
    
    Matrix3 rot;
    rot.setToRotationZ(degrees);
    m_directions *= rot;
}

void
Camera::pitch(float degrees) {
    m_dirty = true;
    
    Matrix3 rot;
    rot.setToRotationX(degrees);
    m_directions *= rot;
}

void
Camera::reset() {
    /*
    Vector3 m_up = Vector3(0.f, 1.0f, 0.f);
    m_directions.setBack(m_initBackwardsPoint);

    Vector3 m_right = m_initBackwardsPoint.cross(m_up);
    m_up = m_initBackwardsPoint.cross(m_right);

    m_directions.setRight(m_right);
    m_directions.setUp(m_up);
    */
    
    this->setPosition(m_initEyePoint);
}
