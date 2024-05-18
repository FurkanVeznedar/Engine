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
}

void App2D::OnDetach()
{
}

void App2D::OnUpdate(Engine::DeltaTime ts)
{
    m_CameraController.OnUpdate(ts);

    //Renderer
    Engine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Engine::RenderCommand::Clear();

    Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());

    Engine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
    Engine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
    Engine::Renderer2D::EndScene();
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
