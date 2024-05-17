#include "App2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>

App2D::App2D()
    : Layer("App2D"), m_CameraController(1280.0f / 720.0f)
{

}

void App2D::OnAttach()
{
    m_SquareVA = Engine::VertexArray::Create();

    float squarevertices[] = {
        -0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
         0.5f,  0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f
    };

    Engine::Ref<Engine::VertexBuffer> SquareVB;
    SquareVB.reset(Engine::VertexBuffer::Create(squarevertices, sizeof(squarevertices)));
    SquareVB->SetLayout({
        { Engine::ShaderDataType::Float3, "a_Position"},
        { Engine::ShaderDataType::Float4, "a_Color"}
    });
    m_SquareVA->AddVertexBuffer(SquareVB);

    uint32_t squareindices[] = {
        0, 1, 2, 2, 3 ,0
    };
    Engine::Ref<Engine::IndexBuffer> SquareIB;
    SquareIB.reset(Engine::IndexBuffer::Create(squareindices, sizeof(squareindices) / sizeof(uint32_t)));
    m_SquareVA->SetIndexBuffer(SquareIB);

    m_FlarColorShader = Engine::Shader::Create("FlatColorShader", Engine::Log::GetShadersDir() + "VertexSrc.txt", Engine::Log::GetShadersDir() + "FragmentSrc.txt");
}

void App2D::OnDetach()
{
}

void App2D::OnUpdate(Engine::DeltaTime ts)
{
    m_CameraController.OnUpdate(ts);

    //Render
    Engine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Engine::RenderCommand::Clear();

    Engine::Renderer::BeginScene(m_CameraController.GetCamera());

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

    std::dynamic_pointer_cast<Engine::OpenGLShader>(m_FlarColorShader)->Use();
    std::dynamic_pointer_cast<Engine::OpenGLShader>(m_FlarColorShader)->SetVec4("u_Color", m_SquareColor);

    Engine::Renderer::SubmitGeometry(m_FlarColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Engine::Renderer::EndScene();
}

void App2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void App2D::OnEvent(Engine::Event& e)
{
    m_CameraController.OnEvent(e);
}
