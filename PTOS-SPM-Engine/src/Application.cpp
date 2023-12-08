#include "Application.h"

namespace PTOS {

	//Application Windows Container

	ApplicationWindows::ApplicationWindows() {
		windows = std::vector<Window*>();
	}

	ApplicationWindows::~ApplicationWindows() {
		for (auto win = begin(); win != end(); win++)
			delete *win;
		windows.clear();
	}

	std::vector<Window*>::const_iterator ApplicationWindows::find(Window* window) {
		auto win = begin();
		while (win != end()) {
			if (*win == window)
				return win;
			win++;
		}
		return win;
	}

	bool ApplicationWindows::add(Window* window) {
		if (has(window)) return false;
		windows.push_back(window);
		return true;
	}

	bool ApplicationWindows::remove(size_t index) {
		if (index < 0 || index >= size()) return false;
		windows.erase(begin() + index);
		return true;
	}

	bool ApplicationWindows::remove(Window* window) {
		for (auto win = begin(); win != end(); win++)
			if (*win == window) {
				windows.erase(win);
				return true;
			}
		return false;
	}

	void ApplicationWindows::handle() {
		size_t i = 0;
		while (i < windows.size()) {
			Window* window = get(i);
			if (window->isShutdown())
				remove(i);
			else if (window->isOpen()) {
				window->update();
				i++;
			}
		}
	}

	//Application

	Application::Application() {
		windows = ApplicationWindows();
	}

	Application::~Application() {
		for (auto win = windows.begin(); win != windows.end(); win++)
			delete *win;
		windows.clear();
	}


}