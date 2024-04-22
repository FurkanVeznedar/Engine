#ifndef _WINDOWSINPUT_H_
#define _WINDOWSINPUT_H_

#include "Engine/Input.h"

namespace Engine {
    class WindowsInput : public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;

        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };
}

#endif // _WINDOWSINPUT_H_