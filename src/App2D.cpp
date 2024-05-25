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
    EN_PROFILE_FUNCTION();

    m_Texture = Engine::Texture2D::Create(Engine::Log::GetAssetsDir() + "Texture/Checkerboard.png");
}

void App2D::OnDetach()
{
}

void App2D::OnUpdate(Engine::DeltaTime ts)
{

    EN_PROFILE_FUNCTION();

    m_CameraController.OnUpdate(ts);

    //Renderer
    Engine::Renderer2D::ResetStats();
    {
        EN_PROFILE_SCOPE("Renderer Prep");
        Engine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Engine::RenderCommand::Clear();
    }

    {
        static float rotate = 0.0;
        rotate += ts * 50.0f;

        EN_PROFILE_SCOPE("Renderer Draw");
        Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());
        Engine::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f) , { 0.8f, 0.2f, 0.3f, 1.0f });
        Engine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
        Engine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
        Engine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_Texture, 10.0f);
        Engine::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotate, m_Texture, 100.0f);
        // Engine::Renderer2D::EndScene();

        // Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());
        for(float y = -5.0f; y < 5.0f; y += 0.5f)
        {
            for(float x = -5.0f; x < 5.0f; x += 0.5f)
            {
                glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (x + 5.0f) / 10.0f, 0.7f };
                Engine::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
            }
        }
        Engine::Renderer2D::EndScene();
    }
}

void App2D::OnImGuiRender()
{
    EN_PROFILE_FUNCTION();

    ImGui::Begin("Settings");

    auto stats = Engine::Renderer2D::GetStats();
    ImGui::Text("Renderer 2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.NumDrawC);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

    ImGui::End();
}

void App2D::OnEvent(Engine::Event& e)
{
    m_CameraController.OnEvent(e);
}
