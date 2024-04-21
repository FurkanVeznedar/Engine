#ifndef _WINDOWSINPUT_H_
#define _WINDOWSINPUT_H_

#include "Engine/Input.h"

namespace Engine {
    class WindowsInput : public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;
    };
}

#endif // _WINDOWSINPUT_H_