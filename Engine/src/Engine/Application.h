#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Engine/Core.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Window.h"
#include "Engine/LayerStack.h"

#include "Engine/ImGui/ImGuiLayer.h"

#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/VertexArray.h"
#include "Engine/Renderer/Camera.h"

namespace Engine {

    class Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverLay(Layer* overlay);

        inline Window& GetWindow() {return *m_Window;}
        
        inline static Application& Get() {return *s_Instance;}
    private:
        bool OnWindowClose(WindowCloseEvent &e);

        std::unique_ptr<Window> m_Window;
        int m_WindowWidth, m_WindowHeight;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_Layerstack;

        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<VertexArray> m_VertexArray;

        std::shared_ptr<Shader> m_BlueShader;
        std::shared_ptr<VertexArray> m_SquareVA;

        std::shared_ptr<Camera> m_Camera;

        static Application* s_Instance;
    };

    // To be defined in client
    Application* CreateApplication();
}
#endif // _APPLICATION_H_