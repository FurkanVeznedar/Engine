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

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& VertexBuffer) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer) override;

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffer; }
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffers() const override { return m_IndexBuffer; }

    private:
        uint32_t m_RendererID;
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}

#endif // _OPENGLVERTEXARRAY_H_