#include "Enpch.h"
#include "Engine/Application.h"

#include <glad/glad.h>

namespace Engine {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        EN_ENGINE_ASSERT(!s_Instance, "Applicatin already excist!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallBack(EN_BIND_EVENT_FN(Application::OnEvent));
    }

    Application::~Application()
    {
    }

    void Application::PushLayer(Layer* layer)
    {
        m_Layerstack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverLay(Layer* overlay)
    {
        m_Layerstack.PushOverLay(overlay);
        overlay->OnAttach();
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(EN_BIND_EVENT_FN(Application::OnWindowClose));

        for(auto it = m_Layerstack.end(); it != m_Layerstack.begin();)
        {
            (*--it)->OnEvent(e);
            if(e.m_Handled) break;
        }
    }

    void Application::Run()
    {
        while(m_Running)
        {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for(Layer* layer : m_Layerstack) layer->OnUpdate();
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent &e)
    {
        m_Running = false;
        return true;
    }
}