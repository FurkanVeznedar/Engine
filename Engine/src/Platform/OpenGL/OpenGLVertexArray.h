#ifndef _OPENGLVERTEXARRAY_H_
#define _OPENGLVERTEXARRAY_H_

#include "Enpch.h"
#include "Engine/Renderer/VertexArray.h"

namespace Engine {

    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void UnBind() const override;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& VertexBuffer) override;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& IndexBuffer) override;

        virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffer; }
        virtual const Ref<IndexBuffer>& GetIndexBuffers() const override { return m_IndexBuffer; }

    private:
        uint32_t m_RendererID;
        std::vector<Ref<VertexBuffer>> m_VertexBuffer;
        Ref<IndexBuffer> m_IndexBuffer;
    };
}

#endif // _OPENGLVERTEXARRAY_H_