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
    m_Texture = Engine::Texture2D::Create(Engine::Log::GetAssetsDir() + "Texture/Checkerboard.png");
}

void App2D::OnDetach()
{
}

void App2D::OnUpdate(Engine::DeltaTime ts)
{

    EN_PROFILE_FUNCTION();

    {
        EN_PROFILE_SCOPE("CameraController::OnUpdate");
        m_CameraController.OnUpdate(ts);
    }

    //Renderer
    {
        EN_PROFILE_SCOPE("Renderer Prep");
        Engine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Engine::RenderCommand::Clear();
    }

    {
        EN_PROFILE_SCOPE("Renderer Draw");
        Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());
        Engine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
        Engine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
        Engine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture);
        Engine::Renderer2D::EndScene();
    }
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
