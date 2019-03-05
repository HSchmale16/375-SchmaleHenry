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
: m_eyePoint(eyePoint), m_backwardsPoint(localBackDirection), 
  m_nearClipPlaneDistance(nearClipPlaneDistance),
  m_farClipPlaneDistance(farClipPlaneDistance), m_aspectRatio(aspectRatio), 
  m_verticalFieldOfViewDegrees(verticalFieldOfViewDegrees),
  m_currentYaw(0),
  m_initEyePoint(m_eyePoint),
  m_initBackwardsPoint(m_backwardsPoint)
{
    m_projectionMat = glm::perspective(
        glm::radians(m_verticalFieldOfViewDegrees),
        m_aspectRatio,
        m_nearClipPlaneDistance,
        m_farClipPlaneDistance);
    
    // use a guess for the initial up vector
    m_up = Vector3(0.f, 1.0f, 0.f);
     
    m_right = m_backwardsPoint.cross(m_up);
    m_up = m_backwardsPoint.cross(m_right);

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
        Vector3 at = m_eyePoint - m_backwardsPoint;
        print_vec(at);
       
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
Camera::setPosition(const Vector3& position) {
    m_eyePoint = position;
    m_dirty = true;
}

void
Camera::yaw(float degrees) {
    m_dirty = true;

    m_backwardsPoint = rotateHelper(m_backwardsPoint, degrees, m_up);
    print_vec(m_backwardsPoint);
    m_right = rotateHelper(m_right, degrees, m_up);
    m_currentYaw += degrees;
}

Vector3
Camera::rotateHelper(const Vector3& target, float degrees, const Vector3& normal) {
    glm::vec3 gTar(target.x, target.y, target.z);
    glm::vec3 norm(normal.x, normal.y, normal.z);

    glm::vec3 res = glm::rotate(gTar, glm::radians(degrees), norm);

    return Vector3(res.x, res.y, res.z);
}

void
Camera::reset() {
    m_up = Vector3(0.f, 1.0f, 0.f);
    m_backwardsPoint = m_initBackwardsPoint;

    m_right = m_backwardsPoint.cross(m_up);
    m_up = m_backwardsPoint.cross(m_right);
    
    this->setPosition(m_initEyePoint);
}
