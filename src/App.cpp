#include "Engine.h"
#include "Enpch.h"

class ExampleLayer : public Engine::Layer
{
public:
    ExampleLayer()
        : Layer("Example") {}
    
    void OnUpdate() override
    {
        if(Engine::Input::IsKeyPressed(EN_KEY_TAB)) EN_APP_INFO("Tab key is pressed!");
        if(Engine::Input::IsMouseButtonPressed(EN_MOUSE_BUTTON_RIGHT)) EN_APP_TRACE("Mouse right is pressed!");
        if(Engine::Input::IsMouseButtonPressed(EN_MOUSE_BUTTON_LEFT)) EN_APP_TRACE("Mouse left is pressed!");
        if(Engine::Input::IsMouseButtonPressed(EN_MOUSE_BUTTON_MIDDLE)) EN_APP_TRACE("Mouse middle is pressed!");
           
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
