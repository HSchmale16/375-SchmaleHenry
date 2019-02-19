#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

Camera::Camera() {}

Camera::Camera(const glm::vec3& eyePoint, const glm::vec3& localBackDirection,
    float nearClipPlaneDistance, float farClipPlaneDistance,
    float aspectRatio, float verticalFieldOfViewDegrees)
: m_eyePoint(eyePoint), m_backwardsPoint(localBackDirection), 
  m_nearClipPlaneDistance(nearClipPlaneDistance),
  m_farClipPlaneDistance(farClipPlaneDistance), m_aspectRatio(aspectRatio), 
  m_verticalFieldOfViewDegrees(verticalFieldOfViewDegrees)
{
    m_projectionMat = glm::perspective(
        glm::radians(m_verticalFieldOfViewDegrees),
        m_aspectRatio,
        m_nearClipPlaneDistance,
        m_farClipPlaneDistance);
    m_up = glm::vec3(0,1,0);
    m_right = glm::cross(m_backwardsPoint, m_up);
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

        m_viewMat = glm::lookAt(m_eyePoint, m_eyePoint, m_up);
        m_dirty = false;
    }
    return m_viewMat;
}

void
Camera::moveUp(float distance) {
    this->m_eyePoint.y += distance;
    m_dirty = true;
}

void
Camera::moveRight(float distance) {
    this->m_eyePoint.x += distance;
    m_dirty = true;
}

void
Camera::moveBack(float distance) {
    this->m_eyePoint.z += distance;
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
    m_right = glm::rotate(m_right, glm::radians(degrees), m_up);
}