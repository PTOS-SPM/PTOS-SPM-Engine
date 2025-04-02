#pragma once

#include "predefines.h"

#include "Input.h"

#include <chrono>
#include <string>

namespace PTOS {
	
	const bool VSYNC_DEFAULT = true;

	struct WindowSize {
		int width;
		int height;
	};

	struct WindowProperties {
		WindowSize size;
		std::string title;
		void* icon;
	};

	struct WindowEvent {
		WindowRenderer* windowRenderer;
		Inputs::Code code = Inputs::CODE_NONE;
		double dx = 0, dy = 0;
	};

	class WindowRenderer
	{
	public:
		WindowRenderer(EventSystem* esys, EventLayer* eventLayer);

		//Gets the window renderer's target event layer
		inline EventLayer* getEventLayer() const { return eventLayer; }
		//Gets the window renderer event system
		inline EventSystem* getEventSystem() const { return esys; }
		//Gets the window renderer's initialization state
		inline bool getInitialized() const { return isInitialized; }
		//Gets the window renderer's shutdown state
		inline bool getShutdown() const { return isShutdown; }
		//Gets the window renderer's vsync setting
		inline bool isVsync() const { return vsync; }
		//Gets the window renderer's width
		inline int getWidth() const { return size.width; }
		//Gets the window renderer's heigth
		inline int getHeight() const { return size.height; }
		//Gets the window renderer's size
		inline WindowSize getSize() const { return size; }
		//Gets the window's title
		inline std::string getTitle() const { return title; }
		inline std::chrono::steady_clock::time_point getLastFrame() const { return lastFrame; }


		//Initializes the window renderer
		virtual void init(const WindowProperties& props) = 0;
		//Shuts down the window renderer
		virtual void shutdown() = 0;
		//Creates a window using the window renderer
		virtual void create() = 0;
		//Destorys a window using the window renderer
		virtual void destroy() = 0;

		//Binds the rendering context to this window renderer
		virtual void bind() = 0;
		//Unbinds the rendering context from this window renderer
		virtual void unbind() = 0;
		//Called by Window::update after handling the frame renderer
		virtual void onUpdate() = 0;

		//Sets window vsync
		virtual void setVsync(bool vsync) = 0;
		//Sets window width
		virtual void setWidth(int width) = 0;
		//Sets window height
		virtual void setHeight(int height) = 0;
		//Sets window width and height
		virtual void setSize(const WindowSize& size) = 0;
		//Sets window title
		virtual void setTitle(const std::string& title) = 0;
		//Gets the window's creation status
		virtual bool isCreated() = 0;
		//Gets the renderer name
		virtual std::string getRendererName() = 0;
		//TODO docs
		virtual void* getImplWindow() = 0;

	protected:

		//Window

		bool isInitialized = false;
		bool isShutdown = false;

		EventSystem* esys = nullptr;
		EventLayer* eventLayer = nullptr;

		WindowSize size = {0,0};
		std::string title = "";
		bool vsync = VSYNC_DEFAULT;

		//Renderer

		inline void setLastFrame() { lastFrame = std::chrono::high_resolution_clock::now(); }

		std::chrono::steady_clock::time_point lastFrame = std::chrono::high_resolution_clock::now();
	};
}