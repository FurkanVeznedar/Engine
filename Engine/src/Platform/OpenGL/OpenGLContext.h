#ifndef _OPENGLCONTEXT_H_
#define _OPENGLCONTEXT_H_

#include "Engine/Renderer/RenderingContext.h"

struct GLFWwindow;

namespace Engine {

    class OpenGLContext : public RenderingContext
    {
    public:
        OpenGLContext(GLFWwindow* WindowHandle);
        ~OpenGLContext();

        virtual void Init() override;
        virtual void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };
}

#endif // _OPENGLCONTEXT_H_