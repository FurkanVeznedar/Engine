#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Core.h"
#include "./Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "LayerStack.h"

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
    private:
        bool OnWindowClose(WindowCloseEvent &e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_Layerstack;
    };

    // To be defined in client
    Application* CreateApplication();
}
#endif // _APPLICATION_H_