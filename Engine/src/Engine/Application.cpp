#include "Enpch.h"
#include "Engine/Application.h"

#include "Engine/Input.h"

#include "Engine/Renderer/Renderer.h"

#include <glfw/glfw3.h>

namespace Engine {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        EN_ENGINE_ASSERT(!s_Instance, "Applicatin already excist!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallBack(EN_BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();

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
        dispatcher.Dispatch<WindowResizeEvent>(EN_BIND_EVENT_FN(Application::OnWindowResize));

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

            if(!m_Minimized)
            {
                for(Layer* layer : m_Layerstack) layer->OnUpdate(deltatime);
            }

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

    bool Application::OnWindowResize(WindowResizeEvent &e)
    {
        if(e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }
}