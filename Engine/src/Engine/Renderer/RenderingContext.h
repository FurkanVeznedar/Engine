#ifndef _RENDERINGCONTEXT_H_
#define _RENDERINGCONTEXT_H_

namespace Engine {

    class RenderingContext
    {
    public:
        RenderingContext() {}

        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
    
}

#endif // _RENDERINGCONTEXT_H_