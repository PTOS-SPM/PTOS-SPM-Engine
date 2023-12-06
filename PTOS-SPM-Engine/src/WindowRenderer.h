#pragma once

#include<GLFW/glfw3.h>

#include "Core.h"

#define PTOS_OVERRIDE_WINDOW_RENDERER_METHODS(name) \
		~name() { shutdown(); } \
		void update() override; \
		void init(const WindowProperties& props) override; \
		void shutdown() override; \
		void create() override; \
		void destroy() override; \
		void setVsync(bool vsync) override; \
		void setWidth(int width) override; \
		void setHeight(int height) override; \
		void setSize(const WindowSize& size) override; \
		void setTitle(const std::string& title) override; \
		inline std::string getRendererName() override { return #name; }

//sets width=0, height=0, bytes=0
#define PTOS_GLFW_ICON_EMPTY {0,0,0}

namespace PTOS {
	struct PTOS_API WindowSize {
		WindowSize() { width = 0; height = 0; }
		WindowSize(int width, int height) {
			this->width = width;
			this->height = height;
		}

		int width;
		int height;
	};

	struct PTOS_API WindowProperties {
		WindowProperties() {
			this->size = WindowSize();
			title = "";
			icon = nullptr;
		}

		WindowProperties(WindowSize size, std::string& title, void* icon) {
			this->size = size;
			this->title = title;
			this->icon = icon;
		}

		WindowSize size;
		std::string title;
		void* icon;
	};

	//abstract class for Window Renderers
	class PTOS_API WindowRenderer
	{
	public:
		WindowRenderer(/*TODO EventLayer* eventLayer */);

		//updates window
		virtual void update() = 0;
		//initializes renderer
		virtual void init(const WindowProperties& props) = 0;
		//shuts down renderer
		virtual void shutdown() = 0;
		//creates a window using the renderer
		virtual void create() = 0;
		//destorys a window using the renderer
		virtual void destroy() = 0;

		virtual void setVsync(bool vsync) = 0;
		virtual void setWidth(int width) = 0;
		virtual void setHeight(int height) = 0;
		virtual void setSize(const WindowSize& size) = 0;
		virtual void setTitle(const std::string& title) = 0;
		virtual inline std::string getRendererName() = 0;

		//TODO inline EventLayer* getEventLayer() const { return eventLayer; }

		inline bool getInitialized() const { return isInitialized; }
		inline bool getShutdown() const { return isShutdown; }
		inline bool isVsync() const { return vsync; }
		inline int getWidth() const { return size.width; }
		inline int getHeight() const { return size.height; }
		inline WindowSize getSize() const { return size; }
		inline std::string getTitle() { return title; }

	protected:
		bool isInitialized = false;
		bool isShutdown = false;

		//TODO EventLayer* eventLayer;

		WindowSize size;
		std::string title = "";
		bool vsync;

	};

	class PTOS_API GLFWRenderer : public WindowRenderer {
	public:
		PTOS_OVERRIDE_WINDOW_RENDERER_METHODS(GLFWRenderer)
	private:
		GLFWimage icon = PTOS_GLFW_ICON_EMPTY;
		GLFWwindow* win = nullptr;
	};
}
