#pragma once

#include "predefines.h"

#include "GLFW/glfw3.h"

#include "Input.h"
#include "WindowRenderer.h"

#include "GLFWWindowRenderer.h"

#include <unordered_map>


//sets width=0, height=0, bytes=0
#define PTOS_GLFW_ICON_EMPTY {0,0,0}

namespace PTOS {
	class GLFWWindowRenderer : public WindowRenderer {
	public:
		GLFWWindowRenderer(EventSystem* esys, EventLayer* eventLayer) : WindowRenderer(esys, eventLayer) {}
		~GLFWWindowRenderer() { shutdown(); }
		void init(const WindowProperties& props) override;
		void shutdown() override;
		void create() override;
		void destroy() override;
		void bind() override;
		void unbind() override;
		void onUpdate() override;
		void setVsync(bool vsync) override;
		void setWidth(int width) override;
		void setHeight(int height) override;
		void setSize(const WindowSize& size) override;
		void setTitle(const std::string& title) override;
		inline std::string getRendererName() override { return "GLFWWindoRenderer"; }
		void* getImplWindow() override;


			inline bool isCreated() override { return win != nullptr; }
		inline GLFWimage* getIcon() { return &icon; }
		void setIcon(GLFWimage& icon);

	private:
		//Window

		GLFWimage icon = PTOS_GLFW_ICON_EMPTY;
		GLFWwindow* win = nullptr;
	};

	const std::unordered_map<int, Inputs::Code> codeMapGLFW = {
		{GLFW_KEY_ESCAPE, Inputs::CODE_KEY_ESC},
		{GLFW_KEY_ENTER, Inputs::CODE_KEY_ENTER},
		{GLFW_KEY_TAB, Inputs::CODE_KEY_TAB},
		{GLFW_KEY_BACKSPACE, Inputs::CODE_KEY_BACKSPACE},
		{GLFW_KEY_INSERT, Inputs::CODE_KEY_INSERT},
		{GLFW_KEY_DELETE, Inputs::CODE_KEY_DEL},
		{GLFW_KEY_RIGHT, Inputs::CODE_KEY_RIGHT},
		{GLFW_KEY_LEFT, Inputs::CODE_KEY_LEFT},
		{GLFW_KEY_DOWN, Inputs::CODE_KEY_DOWN},
		{GLFW_KEY_UP, Inputs::CODE_KEY_UP},
		{GLFW_KEY_PAGE_UP, Inputs::CODE_KEY_PAGE_UP},
		{GLFW_KEY_PAGE_DOWN, Inputs::CODE_KEY_PAGE_DOWN},
		{GLFW_KEY_HOME, Inputs::CODE_KEY_HOME},
		{GLFW_KEY_END, Inputs::CODE_KEY_END},
		{GLFW_KEY_CAPS_LOCK, Inputs::CODE_KEY_CAPS_LOCK},
		{GLFW_KEY_SCROLL_LOCK, Inputs::CODE_KEY_SCROLL_LOCK},
		{GLFW_KEY_NUM_LOCK, Inputs::CODE_KEY_NUM_LOCK},
		{GLFW_KEY_PRINT_SCREEN, Inputs::CODE_KEY_PRINT},
		{GLFW_KEY_PAUSE, Inputs::CODE_KEY_PAUSE},
		{GLFW_KEY_F1, Inputs::CODE_KEY_F1},
		{GLFW_KEY_F2, Inputs::CODE_KEY_F2},
		{GLFW_KEY_F3, Inputs::CODE_KEY_F3},
		{GLFW_KEY_F4, Inputs::CODE_KEY_F4},
		{GLFW_KEY_F5, Inputs::CODE_KEY_F5},
		{GLFW_KEY_F6, Inputs::CODE_KEY_F6},
		{GLFW_KEY_F7, Inputs::CODE_KEY_F7},
		{GLFW_KEY_F8, Inputs::CODE_KEY_F8},
		{GLFW_KEY_F9, Inputs::CODE_KEY_F9},
		{GLFW_KEY_F10, Inputs::CODE_KEY_F10},
		{GLFW_KEY_F11, Inputs::CODE_KEY_F11},
		{GLFW_KEY_F12, Inputs::CODE_KEY_F12},
		{GLFW_KEY_F13, Inputs::CODE_KEY_F13},
		{GLFW_KEY_F14, Inputs::CODE_KEY_F14},
		{GLFW_KEY_F15, Inputs::CODE_KEY_F15},
		{GLFW_KEY_F16, Inputs::CODE_NONE},
		{GLFW_KEY_F17, Inputs::CODE_NONE},
		{GLFW_KEY_F18, Inputs::CODE_NONE},
		{GLFW_KEY_F19, Inputs::CODE_NONE},
		{GLFW_KEY_F20, Inputs::CODE_NONE},
		{GLFW_KEY_F21, Inputs::CODE_NONE},
		{GLFW_KEY_F22, Inputs::CODE_NONE},
		{GLFW_KEY_F23, Inputs::CODE_NONE},
		{GLFW_KEY_F24, Inputs::CODE_NONE},
		{GLFW_KEY_F25, Inputs::CODE_NONE},
		{GLFW_KEY_KP_0, Inputs::CODE_KEY_KP_0},
		{GLFW_KEY_KP_1, Inputs::CODE_KEY_KP_1},
		{GLFW_KEY_KP_2, Inputs::CODE_KEY_KP_2},
		{GLFW_KEY_KP_3, Inputs::CODE_KEY_KP_3},
		{GLFW_KEY_KP_4, Inputs::CODE_KEY_KP_4},
		{GLFW_KEY_KP_5, Inputs::CODE_KEY_KP_5},
		{GLFW_KEY_KP_6, Inputs::CODE_KEY_KP_6},
		{GLFW_KEY_KP_7, Inputs::CODE_KEY_KP_7},
		{GLFW_KEY_KP_8, Inputs::CODE_KEY_KP_8},
		{GLFW_KEY_KP_9, Inputs::CODE_KEY_KP_9},
		{GLFW_KEY_KP_DECIMAL, Inputs::CODE_KEY_KP_PERIOD},
		{GLFW_KEY_KP_DIVIDE, Inputs::CODE_KEY_KP_DIVIDE},
		{GLFW_KEY_KP_MULTIPLY, Inputs::CODE_KEY_KP_MULTIPLY},
		{GLFW_KEY_KP_SUBTRACT, Inputs::CODE_KEY_KP_MINUS},
		{GLFW_KEY_KP_ADD, Inputs::CODE_KEY_KP_PLUS},
		{GLFW_KEY_KP_ENTER, Inputs::CODE_KEY_KP_ENTER},
		{GLFW_KEY_KP_EQUAL, Inputs::CODE_KEY_KP_EQUALS},
		{GLFW_KEY_LEFT_SHIFT, Inputs::CODE_KEY_SHIFT_LEFT},
		{GLFW_KEY_RIGHT_SHIFT, Inputs::CODE_KEY_SHIFT_RIGHT},
		{GLFW_KEY_LEFT_CONTROL, Inputs::CODE_KEY_CONTROL_LEFT},
		{GLFW_KEY_RIGHT_CONTROL, Inputs::CODE_KEY_CONTROL_RIGHT},
		{GLFW_KEY_LEFT_ALT, Inputs::CODE_KEY_ALT_LEFT},
		{GLFW_KEY_RIGHT_ALT, Inputs::CODE_KEY_ALT_RIGHT},
		{GLFW_KEY_LEFT_SUPER, Inputs::CODE_KEY_COMMAND_LEFT},
		{GLFW_KEY_RIGHT_SUPER, Inputs::CODE_KEY_COMMAND_RIGHT}
	};
}

