#include "Window.h"
#include "GLFWShader.h"
#include "GLFWWindowRenderer.h"


namespace PTOS {
	Window::Window(const WindowProperties& props, WindowRenderer* windowRenderer, Renderer* renderer) {
		this->windowRenderer = windowRenderer;
		this->renderer = renderer;
		windowRenderer->init(props);
	}

	Window::~Window() {
		delete windowRenderer;
		delete renderer;
	}

	void Window::open() {
		windowRenderer->create();
		renderer->init();
	}

	void Window::close() {
		windowRenderer->destroy();
	}

	bool Window::update() {
		if (windowRenderer->getDeltaTime() >= framerate) {
			windowRenderer->bind();
			
			renderer->setClearColor(rgbaHexToP(0x33, 0x33, 0x33)); //DEBUG color, set as some sort of attribute later
			renderer->clear();

			renderer->submit(scene);

			windowRenderer->onUpdate();

			return true;
		}
		return false;
	}
}