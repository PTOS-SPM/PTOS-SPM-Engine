#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

#include "EventSystem.h"
#include "Input.h"
#include "GLFWWindowRenderer.h"
#include "Log.h"
#include "WindowRenderer.h"


static void glfwErrorCallback(int code, const char* description) {
	PTOS_CORE_ERR("GLFW Error [{0}]: {1}", code, description);
}

namespace PTOS {
	const int VSYNC_INTERVAL = 1; //TODO figure out an actual value to set this to
	static int initializedGLFW = 0; //count number of WindowRenderers using GLFW

	void GLFWWindowRenderer::setVsync(bool vsync) {
		if (vsync)
			glfwSwapInterval(VSYNC_INTERVAL);
		else
			glfwSwapInterval(0);
		PTOS_CORE_TRACE("GLFW WindowRenderer \"{0}\": vsync {1} -> {2}", title, this->vsync, vsync);
		this->vsync = vsync;
	}

	void GLFWWindowRenderer::setWidth(int width) {
		glfwSetWindowSize(win, width, getHeight());
		PTOS_CORE_TRACE("GLFW WindowRenderer \"{0}\": width {1} -> {2}", title, this->size.width, width);
		this->size.width = width;
	}

	void GLFWWindowRenderer::setHeight(int height) {
		glfwSetWindowSize(win, getWidth(), height);
		PTOS_CORE_TRACE("GLFW WindowRenderer \"{0}\": height {1} -> {2}", title, this->size.height, height);
		this->size.height = height;
	}

	void GLFWWindowRenderer::setSize(const WindowSize& size) {
		glfwSetWindowSize(win, size.width, size.height);
		PTOS_CORE_TRACE("GLFW WindowRenderer \"{0}\": size ({1},{2}) -> ({3},{4})", title, this->size.width, this->size.height, size.width, size.height);
		this->size = size;
	}

	void GLFWWindowRenderer::setTitle(const std::string& title) {
		glfwSetWindowTitle(win, title.c_str());
		PTOS_CORE_TRACE("GLFW WindowRenderer \"{0}\" -> \"{1}\"", this->title, title);
		this->title = title;
	}

	void GLFWWindowRenderer::setIcon(GLFWimage& icon) {
		glfwSetWindowIcon(win, 1, &icon);
		PTOS_CORE_TRACE("GLFW WindowRenderer \"{0}\": icon {1}B ({2}x{3}) -> {4}B ({5}x{6})", title,
			this->icon.width * this->icon.height, this->icon.width, this->icon.height,
			icon.width * icon.height, icon.width, icon.height);
		this->icon = icon;
	}

	void GLFWWindowRenderer::bind() {
		glfwMakeContextCurrent(win);
	}

	void GLFWWindowRenderer::unbind() {
		glfwMakeContextCurrent(nullptr);
	}

	void GLFWWindowRenderer::onUpdate() {
		//check for events
		glfwPollEvents();

		//swap buffers
		glfwSwapBuffers(win);
		setLastFrame();
		esys->addEvent(eventLayer, {EventTypes::WINDOW_UPDATE, PTOS_EVENTDATA WindowEvent{this}});
	}

	void GLFWWindowRenderer::init(const WindowProperties& props) {
		if (isInitialized || isShutdown) {
			PTOS_CORE_WARN("GLFW WindowRenderer \"{0}\" is already initialized", props.title);
			return;
		}

		PTOS_CORE_TRACE("Initializing GLFW WindowRenderer \"{0}\"", props.title);

		isInitialized = true;
		size = props.size;
		title = props.title;
		if (props.icon)
			icon = *(GLFWimage*)props.icon;

		if (!initializedGLFW) {
			int success = glfwInit();
			PTOS_CORE_ASSERT(success, "Could not initialize GLFW.");
			//cite: https://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //opengl 3.3
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //make macos happy
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			PTOS_CORE_TRACE("Initialized GLWF");
			glfwSetErrorCallback(glfwErrorCallback);
		}
		initializedGLFW++;

		PTOS_CORE_INFO("Initialized GLFW WindowRenderer \"{0}\": ({1}, {2})", title, size.width, size.height);
	}

	void GLFWWindowRenderer::shutdown() {
		if (!isInitialized || isShutdown) return;
		isShutdown = true;
		destroy();
		initializedGLFW--;
		if (initializedGLFW < 1) {
			PTOS_CORE_TRACE("Terminating GLFW");
			initializedGLFW = 0;
			glfwTerminate();
			PTOS_CORE_INFO("Terminated GLFW");
		}
		PTOS_CORE_INFO("Shutdown GLFW WindowRenderer \"{0}\"", title);
	}

	void GLFWWindowRenderer::create() {
		//init window with values stored in WindowRenderer
		win = glfwCreateWindow(size.width, size.height, title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(win);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwSetWindowUserPointer(win, this);
		setVsync(this->vsync);
		if (icon.width > 0 && icon.height > 0)
			glfwSetWindowIcon(win, 1, &icon);

		//set callbacks; dispatch events, change EventLayer state for appropriate events
		glfwSetWindowCloseCallback(win, [](GLFWwindow* window) {
			GLFWWindowRenderer* windowRenderer = (GLFWWindowRenderer*)glfwGetWindowUserPointer(window);
			windowRenderer->getEventSystem()->addEvent(windowRenderer->getEventLayer(), {EventTypes::WINDOW_CLOSE, PTOS_EVENTDATA WindowEvent{windowRenderer}});

		});
		glfwSetWindowSizeCallback(win, [](GLFWwindow* window, int width, int height) {
			GLFWWindowRenderer* windowRenderer = (GLFWWindowRenderer*)glfwGetWindowUserPointer(window);
			windowRenderer->getEventSystem()->addEvent(windowRenderer->getEventLayer(), { EventTypes::WINDOW_RESIZE, PTOS_EVENTDATA WindowEvent{windowRenderer, Inputs::CODE_NONE, (double)width, (double)height} });

			WindowSize size;
			size.width = width;
			size.height = height;
			windowRenderer->setSize(size);
		});
		glfwSetWindowPosCallback(win, [](GLFWwindow* window, int xpos, int ypos) {
			GLFWWindowRenderer* windowRenderer = (GLFWWindowRenderer*)glfwGetWindowUserPointer(window);
			windowRenderer->getEventSystem()->addEvent(windowRenderer->getEventLayer(), { EventTypes::WINDOW_MOVE, PTOS_EVENTDATA WindowEvent{windowRenderer, Inputs::CODE_NONE, (double)xpos, (double)ypos} });
		});

		glfwSetKeyCallback(win, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			GLFWWindowRenderer* windowRenderer = (GLFWWindowRenderer*)glfwGetWindowUserPointer(window);

			EventType type;
			if (action == GLFW_PRESS)
				type = EventTypes::WINDOW_KEY_DOWN;
			else if (action == GLFW_RELEASE)
				type = EventTypes::WINDOW_KEY_UP;
			else
				return;

			windowRenderer->getEventSystem()->addEvent(windowRenderer->getEventLayer(), { type, PTOS_EVENTDATA WindowEvent{windowRenderer, codeMapGLFW.count(key) ? codeMapGLFW.at(key) : (Inputs::Code)key} });
		});
		glfwSetMouseButtonCallback(win, [](GLFWwindow* window, int button, int action, int mods) {
			GLFWWindowRenderer* windowRenderer = (GLFWWindowRenderer*)glfwGetWindowUserPointer(window);

			EventType type;
			if (action == GLFW_PRESS)
				type = EventTypes::WINDOW_MOUSE_DOWN;
			else if (action == GLFW_RELEASE)
				type = EventTypes::WINDOW_MOUSE_UP;
			else
				return;

			windowRenderer->getEventSystem()->addEvent(windowRenderer->getEventLayer(), { type, PTOS_EVENTDATA WindowEvent{windowRenderer, PTOS_INPUT_IS_MOUSE(button) ? (Inputs::Code)button : Inputs::CODE_NONE}});
		});
		glfwSetScrollCallback(win, [](GLFWwindow* window, double xoffset, double yoffset) {
			GLFWWindowRenderer* windowRenderer = (GLFWWindowRenderer*)glfwGetWindowUserPointer(window);
			windowRenderer->getEventSystem()->addEvent(windowRenderer->getEventLayer(), { EventTypes::WINDOW_MOUSE_SCROLL, PTOS_EVENTDATA WindowEvent{windowRenderer, Inputs::CODE_NONE, xoffset, yoffset} });
		});
		glfwSetCursorPosCallback(win, [](GLFWwindow* window, double xpos, double ypos) {
			GLFWWindowRenderer* windowRenderer = (GLFWWindowRenderer*)glfwGetWindowUserPointer(window);
			windowRenderer->getEventSystem()->addEvent(windowRenderer->getEventLayer(), { EventTypes::WINDOW_MOUSE_MOVE, PTOS_EVENTDATA WindowEvent{windowRenderer, Inputs::CODE_NONE, xpos, ypos} });
		});

		PTOS_CORE_INFO("GLFW WindowRenderer \"{0}\" created", title);
	}

	void GLFWWindowRenderer::destroy() {
		glfwDestroyWindow(win);
		win = nullptr;
		PTOS_CORE_INFO("GLFW WindowRenderer \"{0}\" destroyed", title);
	}

	void* GLFWWindowRenderer::getImplWindow() {
		return win;
	}

}
