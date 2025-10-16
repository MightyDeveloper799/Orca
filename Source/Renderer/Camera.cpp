#include "Camera.h"

namespace Orca 
{

    Camera::Camera(float fov, float aspect, float nearPlane, float farPlane)
        : m_FOV(fov), m_Aspect(aspect), m_Near(nearPlane), m_Far(farPlane),
        m_Position(0.0f), m_Rotation(0.0f) {}

    void Camera::SetPos(const glm::vec3& position) 
    {
        m_Position = position;
    }

    void Camera::SetRot(const glm::vec3& rotation) 
    {
        m_Rotation = rotation;
    }

    const glm::vec3& Camera::GetPos() const
    {
        return m_Position;
    }

    const glm::vec3& Camera::GetRot() const 
    {
        return m_Rotation;
    }

    glm::mat4 Camera::GetViewMatrix() const 
    {
        glm::vec3 direction;
        direction.x = cos(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));
        direction.y = sin(glm::radians(m_Rotation.x));
        direction.z = sin(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));

        return glm::lookAt(m_Position, m_Position + glm::normalize(direction), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::mat4 Camera::GetProjectionMatrix() const 
    {
        return glm::perspective(glm::radians(m_FOV), m_Aspect, m_Near, m_Far);
    }

}