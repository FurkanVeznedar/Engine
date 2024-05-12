#ifndef _VERTEXARRAY_H_
#define _VERTEXARRAY_H_

#include <memory>
#include "Engine/Renderer/Buffer.h"

namespace Engine {

    class VertexArray
    {
    public:
        virtual ~VertexArray() {}

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& VertexBuffer) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& IndexBuffer) = 0;

        virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const Ref<IndexBuffer>& GetIndexBuffers() const = 0;

        static VertexArray* Create();
    };
}

#endif // _VERTEXARRAY_H_