#ifndef _INPUT_H_
#define _INPUT_H_

#include "Engine/Core.h"

namespace Engine {

    class ENGINE_API Input
    {
    public:
        static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
    protected:
        virtual bool IsKeyPressedImpl(int keycode) = 0;
    private:
        static Input* s_Instance;
    };
}

#endif // _INPUT_H_