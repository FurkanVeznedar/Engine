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

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& VertexBuffer) = 0;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer) = 0;

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffers() const = 0;

        static VertexArray* Create();
    };
}

#endif // _VERTEXARRAY_H_