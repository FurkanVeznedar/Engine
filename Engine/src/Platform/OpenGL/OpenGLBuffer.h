#ifndef _OPENGLBUFFER_h_
#define _OPENGLBUFFER_h_

#include "Engine/Renderer/Buffer.h"

namespace Engine {

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const;
        virtual void UnBind() const;
    private:
        uint32_t m_RendererID;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const;
        virtual void UnBind() const;

        virtual uint32_t GetCount() const;
    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };
}

#endif // _OPENGLBUFFER_h_