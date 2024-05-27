
#include "Enpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>


namespace Engine
{

    Camera::Camera(const float& aspectratio, const float& fov)
        : m_ProjectionMatrix(glm::perspective(glm::radians(fov), aspectratio, 0.1f, 100.0f)), m_ViewMatrix(glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)))
    {
        EN_PROFILE_FUNCTION();

        m_VPMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void Camera::RecalculateViewMatrix()
    {
        EN_PROFILE_FUNCTION();

        m_ViewMatrix = glm::translate(m_ViewMatrix, m_Position);
        m_VPMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void Camera::SetProjectionMatrix(const float& aspectratio, const float& fov)
    {
        EN_PROFILE_FUNCTION();

        m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectratio, 0.1f, 100.0f);
        m_VPMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void Camera::SetViewMatrix(const glm::vec3& camerapos, const glm::vec3& camerafront, const glm::vec3& cameraup)
    {
        EN_PROFILE_FUNCTION();

        m_ViewMatrix = glm::lookAt(camerapos, camerapos + camerafront, cameraup);
        m_VPMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}
