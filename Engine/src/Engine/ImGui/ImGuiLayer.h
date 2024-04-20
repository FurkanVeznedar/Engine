#ifndef _IMGUILAYER_H_
#define _IMGUILAYER_H_

#include "Engine/Layer.h"


namespace Engine {
    class ENGINE_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& event);
    private:
        float m_Time = 0.0f;
    };    
}

#endif // _IMGUILAYER_H_