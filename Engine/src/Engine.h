#ifndef _ENGINE_H_
#define _ENGINE_H_

// For use by Engine applications
#include "Engine/Application.h"
#include "Engine/Window.h"
#include "Engine/Layer.h"
#include "Engine/Log.h"

#include "Engine/Core/DeltaTime.h"

#include "Engine/Input.h"
#include "Engine/KeyCodes.h"
#include "Engine/MouseButtonCodes.h"

#include "Engine/ImGui/ImGuiLayer.h"

//---Renderer-------------------
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/RenderCommand.h"

#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Texture.h"
#include "Engine/Renderer/VertexArray.h"

#include "Engine/Renderer/Camera.h"
//---Renderer-------------------

//---OpenGL-------------------
#include "Platform/OpenGL/OpenGLShader.h"

//---Entry Point----------------
#include "Engine/EntryPoint.h"
//---Entry Point----------------

#endif // _ENGINE_H_