#pragma once

#include "WindowRenderer.h"

namespace PTOS {
	class PTOS_API GLFWRenderer : public WindowRenderer {
	public:
		PTOS_OVERRIDE_WINDOW_RENDERER_METHODS(GLFWRenderer)
		inline bool isCreated() override { return win != nullptr; }
		inline GLFWimage* getIcon() { return &icon; }
		void setIcon(GLFWimage& icon);
	private:
		GLFWimage icon = PTOS_GLFW_ICON_EMPTY;
		GLFWwindow* win = nullptr;
	};
}

