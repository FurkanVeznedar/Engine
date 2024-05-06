#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Engine/Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Window.h"
#include "Engine/LayerStack.h"

#include "Engine/ImGui/ImGuiLayer.h"

namespace Engine {

    class Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverLay(Layer* overlay);

        inline Window& GetWindow() {return *m_Window;}

        static float GetWindowWidth() { return m_WindowWidth;}
        static float GetWindowHeight() { return m_WindowHeight;}
        
        inline static Application& Get() {return *s_Instance;}
    private:
        bool OnWindowClose(WindowCloseEvent &e);
    private:
        std::unique_ptr<Window> m_Window;
        static float m_WindowWidth, m_WindowHeight;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_Layerstack;
    private:
        static Application* s_Instance;
    };

    // To be defined in client
    Application* CreateApplication();
}
#endif // _APPLICATION_H_