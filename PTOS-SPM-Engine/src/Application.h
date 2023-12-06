#pragma once

#include <vector>

#include "Core.h"
#include "Window.h"

namespace PTOS {

	struct PTOS_API ApplicationContext {
		//TODO EventStack* eventStack
	};

	class PTOS_API ApplicationWindows {
	public:

		ApplicationWindows();
		~ApplicationWindows();

		inline size_t size() const { return windows.size(); }
		inline Window* get(int index) { return windows.at(index); }
		inline void clear() { return windows.clear(); }
		inline std::vector<Window*>::const_iterator begin() const { return windows.begin(); }
		inline std::vector<Window*>::const_iterator end() const { return windows.end(); }
		inline bool has(Window* window) { return find(window) != end(); }

		std::vector<Window*>::const_iterator find(Window* window);
		bool add(Window* window);
		bool remove(size_t index);
		bool remove(Window* window);

	private:
		std::vector<Window*> windows;
	};

	class PTOS_API Application
	{
	public:
		Application();
		~Application();
		ApplicationWindows windows;

		inline bool doRun() const { return run; }

	private:
		bool run = true;
	};

	Application* startApplication(PTOS::ApplicationContext& ctx);
	void endApplication(Application* application);
}
