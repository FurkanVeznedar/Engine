#include "Engine.h"
#include "Enpch.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Engine::Layer
{
public:
    ExampleLayer()
        : Layer("Example"), m_SquarePosition(0.0f)
    {
        m_VertexArray.reset(Engine::VertexArray::Create());

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };
        std::shared_ptr<Engine::VertexBuffer> vertexbuffer;
        vertexbuffer.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));

        Engine::BufferLayout layout = {
            { Engine::ShaderDataType::Float3, "a_Position"},
            { Engine::ShaderDataType::Float4, "a_Color"}
        };
        vertexbuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexbuffer);

        uint32_t indices[] = {
            0, 1, 2
        };
        std::shared_ptr<Engine::IndexBuffer> indexbuffer;
        indexbuffer.reset(Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexbuffer);

        m_SquareVA.reset(Engine::VertexArray::Create());

        float squarevertices[] = {
            -0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.5f,  0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f
        };

        std::shared_ptr<Engine::VertexBuffer> SquareVB;
        SquareVB.reset(Engine::VertexBuffer::Create(squarevertices, sizeof(squarevertices)));
        SquareVB->SetLayout({
            { Engine::ShaderDataType::Float3, "a_Position"},
            { Engine::ShaderDataType::Float4, "a_Color"}
        });
        m_SquareVA->AddVertexBuffer(SquareVB);

        uint32_t squareindices[] = {
            0, 1, 2, 2, 3 ,0
        };
        std::shared_ptr<Engine::IndexBuffer> SquareIB;
        SquareIB.reset(Engine::IndexBuffer::Create(squareindices, sizeof(squareindices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(SquareIB);

        m_Shader.reset(Engine::Shader::Create(Engine::Log::GetShadersDir() + "VertexSrc.txt", Engine::Log::GetShadersDir() + "FragmentSrc.txt"));
        m_BlueShader.reset(Engine::Shader::Create(Engine::Log::GetShadersDir() + "VertexSrc.txt", Engine::Log::GetShadersDir() + "FragmentSrc.txt"));

        m_Camera.reset(new Engine::Camera(Engine::Application::GetWindowWidth(), Engine::Application::GetWindowHeight()));
    }
    
    void OnUpdate(Engine::DeltaTime ts) override
    {
        if(Engine::Input::IsKeyPressed(EN_KEY_J)) m_SquarePosition.x -= m_SquarePositionSpeed * ts;
        else if(Engine::Input::IsKeyPressed(EN_KEY_L)) m_SquarePosition.x += m_SquarePositionSpeed * ts;

        if(Engine::Input::IsKeyPressed(EN_KEY_I)) m_SquarePosition.y += m_SquarePositionSpeed * ts;
        else if(Engine::Input::IsKeyPressed(EN_KEY_K)) m_SquarePosition.y -= m_SquarePositionSpeed * ts;

        Engine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Engine::RenderCommand::Clear();

        Engine::Renderer::BeginScene(m_Camera);

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        for(int i = 0; i < 20; i++)
        {
            for(int j = 0; j < 20; j++)
            {
                glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Engine::Renderer::SubmitGeometry(m_BlueShader, m_SquareVA, transform);
            }

        }

        Engine::Renderer::SubmitGeometry(m_Shader, m_VertexArray);

        Engine::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::End();
    }
    void OnEvent(Engine::Event& event) override
    {
    }
private:
    std::shared_ptr<Engine::Shader> m_Shader;
    std::shared_ptr<Engine::VertexArray> m_VertexArray;

    std::shared_ptr<Engine::Shader> m_BlueShader;
    std::shared_ptr<Engine::VertexArray> m_SquareVA;

    std::shared_ptr<Engine::Camera> m_Camera;

    glm::vec3 m_SquarePosition;
    float m_SquarePositionSpeed = 1.0f;
    };

class App : public Engine::Application
{
public:
    App()
    {
        PushLayer(new ExampleLayer());
    }

    ~App()
    {

    }
};

Engine::Application* Engine::CreateApplication()
{
    return new App();
}
