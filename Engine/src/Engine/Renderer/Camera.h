#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Engine/Core/DeltaTime.h"
#include <glm/glm.hpp>

namespace Engine {

    class Camera
    {
    public:
        static const int X_Direction = 1, Y_Direction = 2, Z_Direction = 3;

        Camera(const float windowwidth, const float windowheight);
        ~Camera();

        void SetProjectionMatrix(const float& fov = 45.0f, const float& windowwidth = 1280.0f, const float& windowheight = 720.0f);

        glm::mat4 GetVPMatrix() const { return m_ProjectionMatrix * m_ViewMatrix; }
        glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
        glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }

        void KeyCallBack();
        void MouseButtonCallBack();
        void MouseScrollCallBack();
        void UpdateCamera();
    private:
        float m_WindowWidth, m_WindowHeight;
        glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
        glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);

        glm::vec3 CameraPos, CameraFront, CameraUp;
        float LastFrame = 0.0f;
        
        float LastCursorPosX, LastCursorPosY;
        float yaw, pitch, fov;
        bool FirstMouse;
    };
}

#endif // _CAMERA_H_