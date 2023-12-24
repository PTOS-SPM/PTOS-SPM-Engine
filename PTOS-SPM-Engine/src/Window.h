#pragma once

#include <chrono>
#include <string>

#include "symbols/window.h"

#include "WindowRenderer.h"

namespace PTOS {

	class Window final {
	public:
		Window (const WindowProperties& props, WindowRenderer* renderer);
		~Window();
		
		void open();
		void close();
		bool update();

		inline WindowRenderer* getRenderer() const { return renderer; }
		inline int getWidth() const { return renderer->getWidth(); }
		inline int getHeight() const { return renderer->getHeight(); }
		inline WindowSize getSize() const { return renderer->getSize(); }
		inline std::string getTitle() const { return renderer->getTitle(); }
		inline float getFramerate() const { return framerate == 0 ? 0 : (1E+9 / framerate); }
		
		inline bool isOpen() { return renderer->isCreated(); }
		inline bool isShutdown() { return renderer->getShutdown(); }

		inline void setWidth(int width) { renderer->setWidth(width); }
		inline void setHeight(int height) { renderer->setHeight(height); }
		inline void setSize(const WindowSize& size) { renderer->setSize(size); }
		inline void setTitle(const std::string& title) { renderer->setTitle(title); }
		inline void setFramerate(float framerate) { this->framerate = framerate == 0 ? 0 : (1E+9 / framerate); }

	private:
		WindowRenderer* renderer;

		//stored as nanoseconds / frame
		float framerate = 0.0f;
		std::chrono::steady_clock::time_point lastFrame = std::chrono::high_resolution_clock::now();
	};
}
