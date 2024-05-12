#ifndef _RENDERCOMMAD_H_
#define _RENDERCOMMAD_H_

#include "Engine/Renderer/RendererAPI.h"

namespace Engine {

    class RenderCommand
    {
    public:
        inline static void Init()
        {
            s_RendererAPI->Init();
        }

        inline static void SetClearColor(const glm::vec4& color)
        {
            s_RendererAPI->SetClearColor(color);
        }

        inline static void Clear()
        {
            s_RendererAPI->Clear();
        }
        
        static void DrawIndexed(const Ref<VertexArray>& vertexarray)
        {
            s_RendererAPI->DrawIndexed(vertexarray);
        }

    private:
        static RendererAPI* s_RendererAPI;
    };  
}

#endif // _RENDERCOMMAD_H_