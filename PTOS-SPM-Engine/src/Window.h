#pragma once

#include <string>

#include "WindowRenderer.h"

#define PTOS_NEW_WINDOW(width, height, title, icon, renderer) \
new PTOS::Window(PTOS::WindowProperties(PTOS::WindowSize(width, height), \
std::string(title), icon), renderer)

namespace PTOS {

	class PTOS_API Window
	{
	public:
		Window (const WindowProperties& props, WindowRenderer* renderer);
		~Window();
		
		void open();
		void close();
		void update();

		inline WindowRenderer* getRenderer() const { return renderer; }
		inline int getWidth() const { return renderer->getWidth(); }
		inline int getHeight() const { return renderer->getHeight(); }
		inline WindowSize getSize() const { return renderer->getSize(); }
		inline std::string getTitle() const { return renderer->getTitle(); }

		inline void setWidth(int width) { renderer->setWidth(width); }
		inline void setHeight(int height) { renderer->setHeight(height); }
		inline void setSize(const WindowSize& size) { renderer->setSize(size); }
		inline void setTitle(const std::string& title) { renderer->setTitle(title); }
		inline bool isOpen() { return renderer->isCreated(); }
		inline bool isShutdown() { return renderer->getShutdown(); }

	private:
		WindowRenderer* renderer;
	};
}
