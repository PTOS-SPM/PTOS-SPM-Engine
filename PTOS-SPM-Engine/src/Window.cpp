#include <iostream>

#include "Window.h"


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

	void Window::update() { renderer->update(); }
}

std::ostream& operator<< (std::ostream& out, PTOS::Window& window) {
	return out << "<Window \"" << window.getTitle() << "\" (" << window.getWidth()
		<< "x" << window.getHeight() << ") at " << &window << ">";
}