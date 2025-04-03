#pragma once

#include "predefines.h"
#include "Renderer.h"
#include "WindowRenderer.h"

#include <string>

namespace PTOS {

	class Window final {
	public:
		Window(const WindowProperties& props, WindowRenderer* windowRenderer, Renderer* renderer);
		~Window();

		//Gets this window's window renderer
		inline WindowRenderer* getWindowRenderer() const { return windowRenderer; }
		//Gets this window's frame renderer
		inline Renderer* getRenderer() const { return renderer; }

		//Gets the window renderer's width
		inline int getWidth() const { return windowRenderer->getWidth(); }
		//Gets the window renderer's height
		inline int getHeight() const { return windowRenderer->getHeight(); }
		//Gets the window renderer's width and height
		inline WindowSize getSize() const { return windowRenderer->getSize(); }
		//Gets the window's title
		inline std::string getTitle() const { return windowRenderer->getTitle(); }
		//Gets the window's framerate
		inline float getFramerate() const { return framerate == 0 ? 0 : (1E+9f / framerate); }
		//Gets the window's current scene info
		inline SceneInfo* getScene() const { return scene; }

		//Gets the open state of the window
		inline bool isOpen() { return windowRenderer->isCreated(); }
		//Gets the shutdown state of the window
		inline bool isShutdown() { return windowRenderer->getShutdown(); }

		//Sets the window renderer's width
		inline void setWidth(int width) { windowRenderer->setWidth(width); }
		//Sets the window renderer's height
		inline void setHeight(int height) { windowRenderer->setHeight(height); }
		//Sets the window renderer's width and height
		inline void setSize(const WindowSize& size) { windowRenderer->setSize(size); }
		//Sets the window's title
		inline void setTitle(const std::string& title) { windowRenderer->setTitle(title); }
		//Sets the window's framerate
		inline void setFramerate(float framerate) { this->framerate = framerate == 0 ? 0 : (1E+9f / framerate); }
		//Sets the window's current scene info
		inline void setScene(SceneInfo* scene) { this->scene = scene; }

		//Tells the window renderer to open the window
		void open();
		//Tells the window renderer to close the window
		void close();
		//Invokes the window renderer and frame renderer while maintaining the window's framerate
		bool update();

	protected:
		WindowRenderer* windowRenderer;
		Renderer* renderer;
		SceneInfo* scene;

	private:
		//stored as nanoseconds / frame
		float framerate = 0.0f;
	};
}