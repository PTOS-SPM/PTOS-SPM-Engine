#pragma once

//Predefines

#include "predefines.h"

//Normal Includes

#include "Application.h"
#include "Buffer.h"
#include "Camera.h"
#include "ComponentTransform.h"
#include "EventSystem.h"

#if defined(PTOS_RENDER_GL) || defined(PTOS_RENDER_DYNAMIC)
#include "GLFWBuffer.h"
#include "GLFWRenderer.h"
#include "GLFWShader.h"
#include "GLFWTexture.h"
#include "GLFWVertexArray.h"
#include "GLFWWindowRenderer.h"
#endif

#include "Input.h"
#include "Log.h"
#include "ptosmath.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Window.h"
#include "WindowRenderer.h"

//Entry Point

#include "Core.h"
#include "Start.h"