#ifndef CAMERA_H_INC
#define CAMERA_H_INC

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>


/**
 * Camera.h
 * A basic camera class for opengl stuff
 *
 * Henry J Schmale
 * Feb 26, 2019
 *
 */

class Camera {
public:
    Camera();
    Camera(const glm::vec3& eyePoint, const glm::vec3& localBackDirection,
            float nearClipPlaneDistance, float farClipPlaneDistance,
            float aspectRatio, float verticalFieldOfViewDegrees);


    void
    setPosition(const glm::vec3& position);

    void
    moveRight(float distance);

    void 
    moveUp(float distance);

    void
    moveBack(float distance);

    void
    yaw(float degrees);

    glm::mat4
    getViewMatrix();

    void
    setProjection (float verticalFovDegrees, float aspectRatio,
            float nearZ, float farZ);

    glm::mat4
    getProjectionMatrix() const;

    void
    reset();
private:

    bool m_dirty;

    glm::vec3 m_eyePoint;
    glm::vec3 m_backwardsPoint;
    glm::vec3 m_right;
    glm::vec3 m_up;
    float m_nearClipPlaneDistance;
    float m_farClipPlaneDistance;
    float m_aspectRatio;
    float m_verticalFieldOfViewDegrees;
    float m_currentYaw;
    glm::mat4 m_viewMat;
    glm::mat4 m_projectionMat;

    glm::vec3 m_initEyePoint;
    glm::vec3 m_initBackwardsPoint;
};

#endif // CAMERA_H_INC
