#include "Enpch.h"
#include "Engine/Core/Application.h"

#include "Engine/Core/Input.h"

#include "Engine/Renderer/Renderer.h"

#include <glfw/glfw3.h>

namespace Engine {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        EN_PROFILE_FUNCTION();

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
        EN_PROFILE_FUNCTION();

        m_Layerstack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverLay(Layer* overlay)
    {
        EN_PROFILE_FUNCTION();

        m_Layerstack.PushOverLay(overlay);
        overlay->OnAttach();
    }

    void Application::OnEvent(Event& e)
    {
        EN_PROFILE_FUNCTION();

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
        EN_PROFILE_FUNCTION();
        
        while(m_Running)
        {
            EN_PROFILE_SCOPE("Run Loop");

            float CurrentFrame = static_cast<float>(glfwGetTime());
            DeltaTime deltatime = CurrentFrame - m_LastFrame;
            m_LastFrame = CurrentFrame;

            if(!m_Minimized)
            {
                EN_PROFILE_SCOPE("Layerstack OnUpdate");

                for(Layer* layer : m_Layerstack) layer->OnUpdate(deltatime);
            }

            m_ImGuiLayer->Begin();
            {
                EN_PROFILE_SCOPE("Layerstack OnImGuiRender");
                for(Layer* layer : m_Layerstack) layer->OnImGuiRender();
            }
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
        EN_PROFILE_FUNCTION();
        
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