#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Engine/Core/DeltaTime.h"
#include <glm/glm.hpp>

namespace Engine {

    class Camera
    {
    public:
        static const int X_Direction = 1, Y_Direction = 2, Z_Direction = 3;

        Camera(const float& aspectratio = 1280.0f / 720.0f, const float& fov = 45.0f);
        virtual ~Camera() = default;

        void SetProjectionMatrix(const float& aspectratio, const float& fov = 45.0f);
        void SetViewMatrix(const glm::vec3& camerapos, const glm::vec3& camerafront, const glm::vec3& cameraup);

        glm::vec3 GetPosition() { return m_Position; }
        void SetPosition(glm::vec3& posiiton) { m_Position = posiiton; RecalculateViewMatrix(); }

        glm::mat4 GetVPMatrix() const { return m_ProjectionMatrix * m_ViewMatrix; }
        glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
        glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
    private:
        void RecalculateViewMatrix();
    private:
        glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
        glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
        glm::mat4 m_VPMatrix = glm::mat4(1.0f);

        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
    };
}

#endif // _CAMERA_H_