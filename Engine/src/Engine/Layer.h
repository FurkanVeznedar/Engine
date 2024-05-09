#ifndef _LAYER_H_
#define _LAYER_H_

#include "Engine/Core.h"
#include "Engine/Events/Event.h"
#include "Engine/Core/DeltaTime.h"

namespace Engine {

    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(DeltaTime ts) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };
}

#endif // _LAYER_H_