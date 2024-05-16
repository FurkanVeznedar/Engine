#ifndef _ORTHOGRAPHICCAMERA_H_
#define _ORTHOGRAPHICCAMERA_H_

#include "Engine/Core/DeltaTime.h"
#include <glm/glm.hpp>

namespace Engine {

    class OrthographicCamera
    {
    public:

        OrthographicCamera(float left, float right, float bottom, float top);
        virtual ~OrthographicCamera() = default;

        void SetProjectionMatrix(float left, float right, float bottom, float top);

        glm::vec3 GetPosition() { return m_Position; }
        void SetPosition(glm::vec3& posiiton) { m_Position = posiiton; RecalculateViewMatrix(); }

        float GetRotation() { return m_Rotation; }
        void SetRotation(float& rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

        const glm::mat4& GetVPMatrix() const { return m_VPMatrix; }
        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

    private:
        void RecalculateViewMatrix();
    private:
        glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
        glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
        glm::mat4 m_VPMatrix = glm::mat4(1.0f);

        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
        float m_Rotation = 0.0f;
    };
}

#endif // _ORTHOGRAPHICCAMERA_H_