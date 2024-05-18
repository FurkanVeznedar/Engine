#ifndef _ENGINE_H_
#define _ENGINE_H_

// For use by Engine applications
#include "Engine/Core/Application.h"
#include "Engine/Core/Window.h"
#include "Engine/Core/Layer.h"
#include "Engine/Core/Log.h"

#include "Engine/Core/DeltaTime.h"

#include "Engine/Core/Input.h"
#include "Engine/Core/KeyCodes.h"
#include "Engine/Core/MouseButtonCodes.h"

#include "Engine/ImGui/ImGuiLayer.h"

//---Renderer-------------------
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Renderer2D.h"
#include "Engine/Renderer/RenderCommand.h"

#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Texture.h"
#include "Engine/Renderer/VertexArray.h"

#include "Engine/Renderer/Camera.h"
#include "Engine/Renderer/OrthographicCamera.h"
#include "Engine/Renderer/OrthographicCameraController.h"
//---Renderer-------------------

//---OpenGL-------------------
#include "Platform/OpenGL/OpenGLShader.h"

#endif // _ENGINE_H_