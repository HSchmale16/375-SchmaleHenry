#ifndef CAMERA_H_INC
#define CAMERA_H_INC

#include "Transform.h"
#include "Matrix4.h"

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
    Camera(const Vector3& eyePoint, const Vector3& localBackDirection,
            float nearClipPlaneDistance, float farClipPlaneDistance,
            float aspectRatio, float verticalFieldOfViewDegrees);


    void
    setPosition(const Vector3& position);

    void
    moveRight(float distance);

    void 
    moveUp(float distance);

    void
    moveBack(float distance);

    void
    yaw(float degrees);

    void
    roll(float degrees);

    void
    pitch(float degrees);

    Transform
    getViewMatrix();

    void
    setProjection (float verticalFovDegrees, float aspectRatio,
            float nearZ, float farZ);

    Matrix4
    getProjectionMatrix() const;

    void
    reset();
private:

    bool m_dirty;

    Transform m_world;
    float m_nearClipPlaneDistance;
    float m_farClipPlaneDistance;
    float m_aspectRatio;
    float m_verticalFieldOfViewDegrees;
    float m_currentYaw;
    Matrix4 m_projectionMat;

    Vector3 m_initEyePoint;
    Vector3 m_initBackwardsPoint;

    Vector3
    rotateHelper(const Vector3& target, float degrees, const Vector3& normal);
};

#endif // CAMERA_H_INC
