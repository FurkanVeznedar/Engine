#include "Engine.h"
#include "Enpch.h"

#include "imgui/imgui.h"

class ExampleLayer : public Engine::Layer
{
public:
    ExampleLayer()
        : Layer("Example") {}
    
    void OnUpdate() override
    {
        if(Engine::Input::IsKeyPressed(EN_KEY_TAB)) EN_APP_INFO("Tab key is pressed!");
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("Hello World");
        ImGui::End();
    }
    void OnEvent(Engine::Event& event) override
    {
        // EN_APP_TRACE("{0}", event);
    }
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
