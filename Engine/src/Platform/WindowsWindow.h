#ifndef _WINDOWSWINDOW_H_
#define _WINDOWSWINDOW_H_

#include "Engine/Core/Window.h"
#include "Engine/Renderer/RenderingContext.h"

#include <GLFW/glfw3.h>

namespace Engine {

    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override;
        inline unsigned int GetHeight() const override;

        // Window attributes
        inline void SetEventCallBack(const EventCallBackFn& callback) override;
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        inline virtual void* GetNativeWindow() const { return m_Window; }

    private:
        virtual void Init(const WindowProps& props);
        virtual void ShutDown();
    private:
        GLFWwindow* m_Window;
        RenderingContext* m_Context;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallBackFn EventCallBack;
        };

        WindowData m_Data;
    };
}

#endif // _WINDOWSWINDOW_H_