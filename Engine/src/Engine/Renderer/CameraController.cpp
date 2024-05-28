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

        m_Camera.SetProjectionMatrix(aspectratio, fov);
    }

    void CameraController::OnUpdate(DeltaTime ts)
    {
        EN_PROFILE_FUNCTION();

        float cameraspeed = 2.5f * ts;

        if(Input::IsKeyPressed(EN_KEY_W)) m_CameraPos += cameraspeed * m_CameraFront;
        if(Input::IsKeyPressed(EN_KEY_S)) m_CameraPos -= cameraspeed * m_CameraFront;
        if(Input::IsKeyPressed(EN_KEY_A)) m_CameraPos -=  glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * cameraspeed;
        if(Input::IsKeyPressed(EN_KEY_D)) m_CameraPos +=  glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * cameraspeed;

        m_Camera.SetViewMatrix(m_CameraPos, m_CameraFront, m_CameraUp);
        m_Camera.SetProjectionMatrix(m_AspectRatio, m_Fov);
    }

    void CameraController::OnEvent(Event& e)
    {
        EN_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(EN_BIND_EVENT_FN(CameraController::OnMouseScrolled));
        dispatcher.Dispatch<MouseMovedEvent>(EN_BIND_EVENT_FN(CameraController::OnMouseMoved));
        dispatcher.Dispatch<WindowResizeEvent>(EN_BIND_EVENT_FN(CameraController::OnWindowResized));
    }

    bool CameraController::OnMouseMoved(MouseMovedEvent& e)
    {
        EN_PROFILE_FUNCTION();

        // TODO: glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        // TODO: Pitch calue can vary no need to constrained, you can make a func to do it.

        if(m_FirstMove)
        {
            m_LastX = e.GetX();
            m_LastY = e.GetY();
            m_FirstMove = false;
        }

        float xoffset = e.GetX() - m_LastX;
        float yoffset = m_LastY - e.GetY();
        m_LastX = e.GetX();
        m_LastY = e.GetY();

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;
        
        m_Yaw += xoffset;
        m_Pitch += yoffset;

        if(m_Pitch > 89.0f) m_Pitch = 89.0f;
        if(m_Pitch < -89.0f) m_Pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        direction.y = sin(glm::radians(m_Pitch));
        direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_CameraFront = glm::normalize(direction);

        return false;
    }

    bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        EN_PROFILE_FUNCTION();

        m_Fov -= e.GetYOffSet();
        if(m_Fov < 1.0f) m_Fov = 1.0f;
        else if(m_Fov > 45.0f) m_Fov = 45.0f;

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