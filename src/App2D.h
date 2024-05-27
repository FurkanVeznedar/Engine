#ifndef _APP2D_H_
#define _APP2D_H_

#include "Engine.h"

class App2D : public Engine::Layer
{
public:
    App2D();
    virtual ~App2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(Engine::DeltaTime ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(Engine::Event& e) override;
private:
    Engine::CameraController m_CameraController;

    Engine::Ref<Engine::VertexArray> m_SquareVA;
    Engine::Ref<Engine::Shader> m_FlarColorShader;
    Engine::Ref<Engine::Texture2D> m_Texture;

    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};

#endif // _APP2D_H_