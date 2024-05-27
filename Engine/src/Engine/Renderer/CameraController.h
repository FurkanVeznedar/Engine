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

        float GetZoomLevel() const { return m_ZoomLevel; }
        void SetZoomLevel(float level) { m_ZoomLevel = level; }
    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
    private:
        float m_AspectRatio;
        float m_Fov;
        float m_ZoomLevel = 1.0f;
        Camera m_Camera;

        bool m_Rotation;

        glm::vec3 m_CameraPos = { 0.0f, 0.0f, 3.0f };
        glm::vec3 m_CameraFront = { 0.0f, 0.0f, -1.0f };
        glm::vec3 m_CameraUp = { 0.0f, 1.0f, 0.0f };
        float m_CameraRotation = 0.0f;
    };
}


#endif // _CAMERACONTROLLER_H_ 
