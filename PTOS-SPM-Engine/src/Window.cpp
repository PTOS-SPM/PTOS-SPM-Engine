#include <iostream>

#include "Window.h"
#include "WindowRenderer.h"


namespace PTOS {
	Window::Window(const WindowProperties& props, WindowRenderer* renderer) {
		this->renderer = renderer;
		renderer->init(props);
	}
	
	Window::~Window() {
		delete renderer;
	}

	void Window::open() {
		renderer->create();
	}

	void Window::close() {
		renderer->destroy();
	}

	bool Window::update() {
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - lastFrame);
		if (duration.count() >= framerate) {
			renderer->update();
			lastFrame = std::chrono::high_resolution_clock::now();
			return true;
		}
		return false;
	}
}

std::ostream& operator<< (std::ostream& out, PTOS::Window& window) {
	return out << "<Window \"" << window.getTitle() << "\" (" << window.getWidth()
		<< "x" << window.getHeight() << ") at " << &window << ">";
}