#include "Enpch.h"
#include "OrthographicCameraController.h"

#include "Engine/KeyCodes.h"
#include "Engine/MouseButtonCodes.h"
#include "Engine/Input.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace Engine {
    
    OrthographicCameraController::OrthographicCameraController(float aspectratio, bool rotation)
        : m_AspectRatio(aspectratio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
    {
    }

    void OrthographicCameraController::OnUpdate(DeltaTime ts)
    {
        if(Input::IsKeyPressed(EN_KEY_A)) m_CameraPos.x += m_CameraTranslationSpeed * ts;
        else if(Input::IsKeyPressed(EN_KEY_D)) m_CameraPos.x -= m_CameraTranslationSpeed * ts;

        if(Input::IsKeyPressed(EN_KEY_W)) m_CameraPos.y -= m_CameraTranslationSpeed * ts;
        else if(Input::IsKeyPressed(EN_KEY_S)) m_CameraPos.y += m_CameraTranslationSpeed * ts;

        if(m_Rotation)
        {
            if(Input::IsKeyPressed(EN_KEY_Q)) m_CameraRotation -= m_CameraRotaionSpeed * ts;
            else if(Input::IsKeyPressed(EN_KEY_E)) m_CameraRotation += m_CameraRotaionSpeed * ts;

            m_Camera.SetRotation(m_CameraRotation);
        }

        m_Camera.SetPosition(m_CameraPos);
    }

    void OrthographicCameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(EN_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(EN_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));

    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        m_ZoomLevel -= e.GetYOffSet() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

        return false;
    }
    
    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
    {
        m_AspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
        m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

        return false;
    }
    
}