#include "Enpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Engine {

    OpenGLContext::OpenGLContext(GLFWwindow* WindowHandle)
        : m_WindowHandle(WindowHandle)
    {
        EN_ENGINE_ASSERT(WindowHandle, "Window handle is null!")
    }

    OpenGLContext::~OpenGLContext()
    {
    }

    void OpenGLContext::Init()
    {
        EN_PROFILE_FUNCTION();

        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        EN_ENGINE_ASSERT(status, "Failed to initialize GLAD!!");

        EN_ENGINE_INFO("OpenGL Info:");
        EN_ENGINE_INFO("Vendor: {0}",  std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR))));
        EN_ENGINE_INFO("Renderer: {0}",  std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER))));
        EN_ENGINE_INFO("Version: {0}",  std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
    }

    void OpenGLContext::SwapBuffers()
    {
        EN_PROFILE_FUNCTION();

        glfwSwapBuffers(m_WindowHandle);
    }

}