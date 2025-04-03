#pragma once

#include "predefines.h"
#include "EventSystem.h"

#include <string>
#include <vector>

namespace PTOS {

	class Application {
	public:
		Application() {};
		~Application();

		//Get run status of application
		inline bool doRun() const { return run; };
		//Tells the application to stop running
		inline void stop() { run = false; };
		//Gets window at the given index
		inline Window* getWindow(size_t i) { return windows[i]; }

		//Checks if window is owned by this application
		bool hasWindow(Window* window);
		//Adds a window to the application
		//Returns true if window is not already present
		bool addWindow(Window* window);
		//Removes the window at the given index from the application
		//Returns true if index is present
		bool removeWindow(size_t index);
		//Removes the given window from the application
		//Returns true if window is present
		bool removeWindow(Window* window);
		//Removes the window with the given window renderer from the application
		//Returns true if a window with the given window renderer was present
		bool removeWindow(WindowRenderer* windowRenderer);
		//Create a new window with the given renderers and properties
		Window* newWindow(int width, int height, const std::string title, void* icon, WindowRenderer* windowRenderer, Renderer* renderer);
		//Create a new window with the given renderers and structured properties
		Window* newWindow(const WindowProperties& props, WindowRenderer* windowRenderer, Renderer* renderer);
		//Handle windows
		void handle();

	protected:
		std::vector<Window*> windows;
		bool run = true;
	};

	struct ApplicationEvent {
		Application* app;
	};
}