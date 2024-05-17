
#include "Enpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine/Core/KeyCodes.h"
#include "Engine/Core/MouseButtonCodes.h"
#include "Engine/Core/Input.h"

namespace Engine
{

    Camera::Camera(const float windowwidth, const float windowheight)
        : m_WindowWidth(windowwidth), m_WindowHeight(windowheight)
    {
        // Initialize Key Control Variables
        CameraPos = glm::vec3(0.0f, 0.0f,  3.0f);
        CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        CameraUp = glm::vec3(0.0f, 1.0f,  0.0f);

        LastFrame = 0.0f;

        //Initialize Mouse Control Variables
        LastCursorPosX = m_WindowWidth / 2;
        LastCursorPosY = m_WindowHeight / 2;
        yaw = -90.0f;
        pitch = 0.0f;
        fov = 45.0f;
        FirstMouse = true;

        // Initialize Model & Projection Matrices
        m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), m_WindowWidth / m_WindowHeight, 0.1f, 100.0f);
    }

    Camera::~Camera()
    {
    }

    void Camera::SetProjectionMatrix(const float& fov, const float& windowwidth, const float& windowheight)
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(fov), windowwidth / windowheight, 0.1f, 100.0f);
    }

    void Camera::KeyCallBack()
    {
        float CurrentFrame = static_cast<float>(glfwGetTime());
        DeltaTime m_DeltaTime = CurrentFrame - LastFrame;
        LastFrame = CurrentFrame;

        float CameraSpeed = 2.5f * m_DeltaTime;

        if(Input::IsKeyPressed(EN_KEY_W)) CameraPos -= CameraUp * CameraSpeed;
        if(Input::IsKeyPressed(EN_KEY_S)) CameraPos += CameraUp * CameraSpeed;
        if(Input::IsKeyPressed(EN_KEY_A)) CameraPos +=  glm::normalize(glm::cross(CameraFront, CameraUp)) * CameraSpeed;
        if(Input::IsKeyPressed(EN_KEY_D)) CameraPos -=  glm::normalize(glm::cross(CameraFront, CameraUp)) * CameraSpeed;
    }

    void Camera::MouseButtonCallBack()
    {
        if(!Input::IsMouseButtonPressed(EN_MOUSE_BUTTON_LEFT)) return;
        float xpos = Input::GetMouseX();
        float ypos = Input::GetMouseY();

        if (FirstMouse)
        {
            LastCursorPosX = xpos;
            LastCursorPosY = ypos;
            FirstMouse = false;
        }
    
        float xoffset = xpos - LastCursorPosX;
        float yoffset = LastCursorPosY - ypos; 
        LastCursorPosX = xpos;
        LastCursorPosY = ypos;

        float sensitivity = 0.001f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if(pitch > 89.0f) pitch = 89.0f;
        if(pitch < -89.0f) pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        CameraFront = glm::normalize(direction);
    }

    void Camera::MouseScrollCallBack()
    {
        if(!Input::IsMouseButtonPressed(EN_MOUSE_BUTTON_MIDDLE)) return;
        float ypos = Input::GetMouseY();

        float yoffset = LastCursorPosY - ypos;
        LastCursorPosY = ypos;

        fov -= yoffset;
        if (fov < 1.0f) fov = 1.0f;
        if (fov > 45.0f) fov = 45.0f; 
    }

    void Camera::UpdateCamera()
    {
        KeyCallBack();
        m_ViewMatrix = glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);

        MouseButtonCallBack();
        MouseScrollCallBack();
        m_ProjectionMatrix = glm::perspective(glm::radians(fov), m_WindowWidth / m_WindowHeight, 0.1f, 100.0f);
    }
}
