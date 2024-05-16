#ifndef _ORTHOGRAPHICCAMERACONTROLLER_H_
#define _ORTHOGRAPHICCAMERACONTROLLER_H_

#include "Engine/Renderer/OrthographicCamera.h"
#include "Engine/Core/DeltaTime.h"

#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/ApplicationEvent.h"

namespace Engine {

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectratio, bool rotation = false);
        virtual ~OrthographicCameraController() = default;

        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

        void OnUpdate(DeltaTime ts);
        void OnEvent(Event& e);

        float GetZoomLevel() const { return m_ZoomLevel; }
        void SetZoomLevel(float level) { m_ZoomLevel = level; }
    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;

        bool m_Rotation;

        glm::vec3 m_CameraPos = { 0.0f, 0.0f, 0.0f};
        float m_CameraRotation = 0.0f;
        float m_CameraTranslationSpeed = 2.0f, m_CameraRotaionSpeed = 180.0f;
    };
}

#endif // _ORTHOGRAPHICCAMERACONTROLLER_H_