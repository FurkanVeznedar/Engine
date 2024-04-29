#include "Enpch.h"
#include "Engine/Application.h"

#include <glad/glad.h>
#include "Engine/Input.h"

#include "glm/glm.hpp"

namespace Engine {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        EN_ENGINE_ASSERT(!s_Instance, "Applicatin already excist!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallBack(EN_BIND_EVENT_FN(Application::OnEvent));

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
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f
        };

        std::shared_ptr<VertexBuffer> SquareVB;
        SquareVB.reset(VertexBuffer::Create(squarevertices, sizeof(squarevertices)));
        SquareVB->SetLayout({
            { ShaderDataType::Float3, "a_Position"},
        });
        m_SquareVA->AddVertexBuffer(SquareVB);

        uint32_t squareindices[] = {
            0, 1, 2, 2, 3 ,0
        };
        std::shared_ptr<IndexBuffer> SquareIB;
        SquareIB.reset(IndexBuffer::Create(squareindices, sizeof(squareindices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(SquareIB);

        std::string VertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string FragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
            }
        )";

        std::string BlueVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string BlueFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            void main()
            {
                color = vec4(0.2, 0.3, 0.8, 1.0);
            }
        )";

        m_Shader.reset(new Shader(VertexSrc, FragmentSrc));
        m_BlueShader.reset(new Shader(BlueVertexSrc, BlueFragmentSrc));

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
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_BlueShader->Bind();
            m_SquareVA->Bind();
            glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);

            m_Shader->Bind();
            m_VertexArray->Bind();
            glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);

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