#ifndef _IMGUILAYER_H_
#define _IMGUILAYER_H_

#include "Engine/Core/Layer.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/ApplicationEvent.h"

namespace Engine {
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        
        void Begin();
        void End();
    private:
        float m_Time = 0.0f;
    };    
}

#endif // _IMGUILAYER_H_