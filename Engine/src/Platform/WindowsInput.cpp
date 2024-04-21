#include "Enpch.h"
#include "Platform/WindowsInput.h"

#include <GLFW/glfw3.h>

namespace Engine {

    Input* Input::s_Instance = nullptr;

    bool WindowsInput::IsKeyPressedImpl(int keycode)
    {
        // auto& window
        return false;
    }
}