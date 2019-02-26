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
print_vec(const glm::vec3& v) {
    printf("%f %f %f\n", v.x, v.y, v.z);
}

Camera::Camera() {}

Camera::Camera(const glm::vec3& eyePoint, const glm::vec3& localBackDirection,
    float nearClipPlaneDistance, float farClipPlaneDistance,
    float aspectRatio, float verticalFieldOfViewDegrees)
: m_eyePoint(eyePoint), m_backwardsPoint(localBackDirection), 
  m_nearClipPlaneDistance(nearClipPlaneDistance),
  m_farClipPlaneDistance(farClipPlaneDistance), m_aspectRatio(aspectRatio), 
  m_verticalFieldOfViewDegrees(verticalFieldOfViewDegrees),
  m_currentYaw(0)
{
    m_projectionMat = glm::perspective(
        glm::radians(m_verticalFieldOfViewDegrees),
        m_aspectRatio,
        m_nearClipPlaneDistance,
        m_farClipPlaneDistance);
    
    // use a guess for the initial up vector
    m_up = glm::vec3(0.f, 1.0f, 0.f);
     
    m_right = glm::cross(m_backwardsPoint, m_up);
    m_up = glm::cross(m_backwardsPoint, m_right);

    print_vec(m_backwardsPoint);
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
        glm::vec3 at = m_eyePoint - m_backwardsPoint;
        print_vec(at);
        m_viewMat = glm::lookAt(m_eyePoint, at, m_up);
        m_dirty = false;
    }
    return m_viewMat;
}

void
Camera::moveUp(float distance) {
    this->m_eyePoint += m_up * distance;
    m_dirty = true;
}

void
Camera::moveRight(float distance) {
    this->m_eyePoint += m_right * distance;
    m_dirty = true;
}

void
Camera::moveBack(float distance) {
    this->m_eyePoint += m_backwardsPoint * distance;
    m_dirty = true;
}

void
Camera::setPosition(const glm::vec3& position) {
    m_eyePoint = position;
    m_dirty = true;
}

void
Camera::yaw(float degrees) {
    m_dirty = true;
    m_backwardsPoint = glm::rotate(m_backwardsPoint, glm::radians(degrees), m_up);
    print_vec(m_backwardsPoint);
    m_right = glm::rotate(m_right, glm::radians(degrees), m_up);
    m_currentYaw += degrees;
}

void
Camera::resetRotation() {
    this->yaw(-m_currentYaw);
}
