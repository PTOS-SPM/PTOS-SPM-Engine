#include "Application.h"
#include "Window.h"

namespace PTOS {
	
	Application::~Application() {
		for (auto it = windows.begin(); it != windows.end(); it++) {
			delete* it;
		}
		windows.clear();
	}

	bool Application::hasWindow(Window* window) {
		for (auto it = windows.begin(); it != windows.end(); it++)
			if (*it == window)
				return true;
		return false;
	}

	bool Application::addWindow(Window* window) {
		if (hasWindow(window))
			return false;
		windows.push_back(window);
		return true;
	}

	bool Application::removeWindow(size_t index) {
		if (index < 0 || index > windows.size())
			return false;
		windows.erase(windows.begin() + index);
		return true;
	}

	bool Application::removeWindow(Window* window) {
		for (auto it = windows.begin(); it != windows.end(); it++) {
			if (*it == window) {
				windows.erase(it);
				return true;
			}
		}
		return false;
	}

	bool Application::removeWindow(WindowRenderer* windowRenderer) {
		for (auto it = windows.begin(); it != windows.end(); it++) {
			if ((*it)->getWindowRenderer() == windowRenderer) {
				windows.erase(it);
				return true;
			}
		}
		return false;
	}

	Window* Application::newWindow(int width, int height, const std::string title, void* icon, WindowRenderer* windowRenderer, Renderer* renderer) {
		WindowProperties props{ {width, height}, title, icon };
		return newWindow(props, windowRenderer, renderer);
	}

	Window* Application::newWindow(const WindowProperties& props, WindowRenderer* windowRenderer, Renderer* renderer) {
		Window* window = new Window(props, windowRenderer, renderer);
		addWindow(window);
		return window;
	}

	void Application::handle() {
		size_t i = 0;
		for (size_t i = 0; i < windows.size();) {
			Window* window = windows[i];
			if (window->isShutdown())
				removeWindow(i);
			else if (window->isOpen()) {
				window->update();
				i++;
			}
		}
	}
}