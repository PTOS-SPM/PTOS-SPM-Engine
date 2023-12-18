#pragma once

#include <vector>

#include "symbols/application.h"
#include "EventSystem.h"
#include "Hooks.h"
#include "Window.h"

namespace PTOS {

	class ApplicationWindows {
	public:

		ApplicationWindows();
		~ApplicationWindows();

		inline size_t size() const { return windows.size(); }
		inline Window* get(size_t index) { return windows.at(index); }
		inline void clear() { return windows.clear(); }
		inline std::vector<Window*>::const_iterator begin() const { return windows.begin(); }
		inline std::vector<Window*>::const_iterator end() const { return windows.end(); }
		inline bool has(Window* window) { return find(window) != end(); }

		std::vector<Window*>::const_iterator find(Window* window);
		bool add(Window* window);
		bool remove(size_t index);
		bool remove(Window* window);

		void handle();

	private:
		std::vector<Window*> windows;
	};

	class Application
	{
	public:
		Application();
		~Application();
		ApplicationWindows windows;

		inline bool doRun() const { return run; }

	protected:
		bool run = true;
	};

	//define context related data

	struct ApplicationContext {
		Application* app = nullptr;
		EventSystem* eventSystem = nullptr;
	};

	class ApplicationContextManager {
	public:
		ApplicationContextManager(ApplicationContext& ctx) { this->ctx = ctx; }

		inline Application* getApplication() { return ctx.app; }

		Window* newWindow(int width, int heigt, std::string& title, void* icon, WindowRenderer* (*rendererCallback)(EventLayer*));
		EventLayer* newLayer(EventType* types, size_t typeCount);
		EventLayer* newLayer() { return newLayer(nullptr, 0); };

	private:
		ApplicationContext ctx;
	};


	//define hook-in events

	_PTOS_HOOKDEF_CREATE_APPLICATION();
	_PTOS_HOOKDEF_START_APPLICATION();
	_PTOS_HOOKDEF_END_APPLICATION();
	_PTOS_HOOKDEF_PRE_UPDATE();
	_PTOS_HOOKDEF_POST_UPDATE();
}