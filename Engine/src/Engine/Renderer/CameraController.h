#ifndef _CAMERACONTROLLER_H_
#define _CAMERACONTROLLER_H_

#include "Engine/Renderer/Camera.h"
#include "Engine/Core/DeltaTime.h"

#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/ApplicationEvent.h"

namespace Engine {

    class CameraController
    {
    public:
        CameraController(const float& aspectratio = 1280.0f / 720.0f, const float& fov = 45.0f, const bool rotation = false);
        virtual ~CameraController() = default;

        Camera& GetCamera() { return m_Camera; }
        const Camera& GetCamera() const { return m_Camera; }

        void OnUpdate(DeltaTime ts);
        void OnEvent(Event& e);

    private:
        bool OnMouseMoved(MouseMovedEvent& e);
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
    private:
        float m_AspectRatio;
        float m_Fov;
        Camera m_Camera;

        glm::vec3 m_CameraPos = { 0.0f, 0.0f, 3.0f };
        glm::vec3 m_CameraFront = { 0.0f, 0.0f, -1.0f };
        glm::vec3 m_CameraUp = { 0.0f, 1.0f, 0.0f };
        bool m_FirstMove = true;
        float m_LastX = 640.0f, m_LastY = 360.0f;
        //Euler Angles
        float m_Yaw = 0.0f, m_Pitch = 0.0f;
    };
}


#endif // _CAMERACONTROLLER_H_ 
