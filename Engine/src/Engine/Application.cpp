#include "Enpch.h"
#include "Engine/Application.h"

#include "Engine/Input.h"
#include "Engine/KeyCodes.h"

#include "Engine/Renderer/Renderer.h"

namespace Engine {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        EN_ENGINE_ASSERT(!s_Instance, "Applicatin already excist!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallBack(EN_BIND_EVENT_FN(Application::OnEvent));
        m_WindowWidth = m_Window->GetWidth();
        m_WindowHeight = m_Window->GetHeight();

        m_ImGuiLayer = new ImGuiLayer();
        PushOverLay(m_ImGuiLayer);

        m_VertexArray.reset(VertexArray::Create());

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };
        std::shared_ptr<VertexBuffer> vertexbuffer;
        vertexbuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position"},
            { ShaderDataType::Float4, "a_Color"}
        };
        vertexbuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexbuffer);

        uint32_t indices[] = {
            0, 1, 2
        };
        std::shared_ptr<IndexBuffer> indexbuffer;
        indexbuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexbuffer);

        m_SquareVA.reset(VertexArray::Create());

        float squarevertices[] = {
            -0.75f, -0.75f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.75f, -0.75f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.75f,  0.75f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            -0.75f,  0.75f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f
        };

        std::shared_ptr<VertexBuffer> SquareVB;
        SquareVB.reset(VertexBuffer::Create(squarevertices, sizeof(squarevertices)));
        SquareVB->SetLayout({
            { ShaderDataType::Float3, "a_Position"},
            { ShaderDataType::Float4, "a_Color"}
        });
        m_SquareVA->AddVertexBuffer(SquareVB);

        uint32_t squareindices[] = {
            0, 1, 2, 2, 3 ,0
        };
        std::shared_ptr<IndexBuffer> SquareIB;
        SquareIB.reset(IndexBuffer::Create(squareindices, sizeof(squareindices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(SquareIB);

        m_Shader.reset(new Shader(Log::GetShadersDir() + "VertexSrc.txt", Log::GetShadersDir() + "FragmentSrc.txt"));
        m_BlueShader.reset(new Shader(Log::GetShadersDir() + "VertexSrc.txt", Log::GetShadersDir() + "FragmentSrc.txt"));

        m_Camera.reset(new Camera(static_cast<float>(m_WindowWidth), static_cast<float>(m_WindowHeight)));
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

            RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
            RenderCommand::Clear();

            Renderer::BeginScene(m_Camera);
            
            Renderer::SubmitGeometry(m_BlueShader, m_SquareVA);
            Renderer::SubmitGeometry(m_Shader, m_VertexArray);

            Renderer::EndScene();

            for(Layer* layer : m_Layerstack) layer->OnUpdate();

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