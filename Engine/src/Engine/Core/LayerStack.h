#ifndef _LAYERSTACK_H_
#define _LAYERSTACK_H_

#include "Engine/Core/Base.h"
#include "Engine/Core/Layer.h"

#include "Enpch.h"

namespace Engine {

    class LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverLay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverLay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }
    private:
        std::vector<Layer*> m_Layers;
        unsigned int m_LayersInsertIndex = 0;
    };
}

#endif // _LAYERSTACK_H_