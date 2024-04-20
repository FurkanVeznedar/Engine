#include "Engine.h"
#include "Enpch.h"

class ExampleLayer : public Engine::Layer
{
public:
    ExampleLayer()
        : Layer("Example") {}
    
    void OnUpdate() override
    {
        EN_APP_INFO("ExampleLayer::Update");
    }

    void OnEvent(Engine::Event& event) override
    {
        EN_APP_TRACE("{0}", event);
    }
};

class App : public Engine::Application
{
public:
    App()
    {
        PushLayer(new ExampleLayer());
        PushOverLay(new Engine::ImGuiLayer());
    }

    ~App()
    {

    }
};

Engine::Application* Engine::CreateApplication()
{
    return new App();
}
