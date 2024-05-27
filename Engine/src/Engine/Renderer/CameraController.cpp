#include "Enpch.h"
#include "CameraController.h"

#include "Engine/Core/KeyCodes.h"
#include "Engine/Core/MouseButtonCodes.h"
#include "Engine/Core/Input.h"

namespace Engine {

    CameraController::CameraController(const float& aspectratio, const float& fov, const bool rotation)
        : m_Camera(aspectratio), m_AspectRatio(aspectratio), m_Fov(fov)
    {
        EN_PROFILE_FUNCTION();
    }

    void CameraController::OnUpdate(DeltaTime ts)
    {
        EN_PROFILE_FUNCTION();

        float CameraSpeed = 2.5f * ts;

        if(Input::IsKeyPressed(EN_KEY_W)) m_CameraPos += CameraSpeed * m_CameraFront;
        if(Input::IsKeyPressed(EN_KEY_S)) m_CameraPos -= CameraSpeed * m_CameraFront;
        if(Input::IsKeyPressed(EN_KEY_A)) m_CameraPos -=  glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * CameraSpeed;
        if(Input::IsKeyPressed(EN_KEY_D)) m_CameraPos +=  glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * CameraSpeed;

        m_Camera.SetViewMatrix(m_CameraPos, m_CameraFront, m_CameraUp);
    }

    void CameraController::OnEvent(Event& e)
    {
        EN_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(EN_BIND_EVENT_FN(CameraController::OnMouseScrolled));
        dispatcher.Dispatch<MouseButtonPressedEvent>(EN_BIND_EVENT_FN(CameraController::OnMouseButtonPressed));
        dispatcher.Dispatch<WindowResizeEvent>(EN_BIND_EVENT_FN(CameraController::OnWindowResized));
    }

    bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        EN_PROFILE_FUNCTION();

        return false;
    }

    bool CameraController::OnMouseButtonPressed(MouseButtonPressedEvent& e)
    {
        EN_PROFILE_FUNCTION();

        return false;
    }

    bool CameraController::OnWindowResized(WindowResizeEvent& e)
    {
        EN_PROFILE_FUNCTION();

        m_AspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
        m_Camera.SetProjectionMatrix(m_AspectRatio);
        return false;
    }

}