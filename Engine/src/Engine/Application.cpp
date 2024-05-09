#include "Enpch.h"
#include "Engine/Application.h"

#include "Engine/Input.h"

#include "Engine/Renderer/Renderer.h"

#include <glfw/glfw3.h>

namespace Engine {

    Application* Application::s_Instance = nullptr;
    float Application::m_WindowWidth;
    float Application::m_WindowHeight;

    Application::Application()
    {
        EN_ENGINE_ASSERT(!s_Instance, "Applicatin already excist!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallBack(EN_BIND_EVENT_FN(Application::OnEvent));
        m_WindowWidth = static_cast<float>(m_Window->GetWidth());
        m_WindowHeight = static_cast<float>(m_Window->GetHeight());

        m_ImGuiLayer = new ImGuiLayer();
        PushOverLay(m_ImGuiLayer);
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
            float CurrentFrame = static_cast<float>(glfwGetTime());
            DeltaTime deltatime = CurrentFrame - m_LastFrame;
            m_LastFrame = CurrentFrame;

            for(Layer* layer : m_Layerstack) layer->OnUpdate(deltatime);

            m_ImGuiLayer->Begin();
            for(Layer* layer : m_Layerstack) layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent &e)
    {
        m_Running = false;
        return true;
    }
}