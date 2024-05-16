#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Engine/Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Window.h"
#include "Engine/LayerStack.h"
#include "Engine/Core/DeltaTime.h"

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
        
        inline static Application& Get() {return *s_Instance;}
    private:
        bool OnWindowClose(WindowCloseEvent &e);
        bool OnWindowResize(WindowResizeEvent &e);
    private:
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        bool m_Minimized = false;
        LayerStack m_Layerstack;
        float m_LastFrame = 0.0f;
    private:
        static Application* s_Instance;
    };

    // To be defined in client
    Application* CreateApplication();
}
#endif // _APPLICATION_H_