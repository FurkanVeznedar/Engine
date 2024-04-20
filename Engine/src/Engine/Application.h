#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Engine/Core.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Window.h"
#include "Engine/LayerStack.h"

namespace Engine {

    class ENGINE_API Application
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

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_Layerstack;

        static Application* s_Instance;
    };

    // To be defined in client
    Application* CreateApplication();
}
#endif // _APPLICATION_H_