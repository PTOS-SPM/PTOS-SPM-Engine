#include <glad/glad.h>

#include "GLFWRenderer.h"
#include "Log.h"
#include "WindowEvent.h"
#include "WindowRenderer.h"



static void glfwErrorCallback(int code, const char* description) {
	PTOS_CORE_ERR("GLFW Error [{0}]: {1}", code, description);
}

namespace PTOS {
	const int VSYNC_INTERVAL = 1; //TODO figure out an actual value to set this to
	static int initializedGLFW = 0; //count number of WindowRenderers using GLFW

	void GLFWRenderer::setVsync(bool vsync) {
		if (vsync)
			glfwSwapInterval(VSYNC_INTERVAL);
		else
			glfwSwapInterval(0);
		PTOS_CORE_TRACE("GLFW WindowRenderer \"{0}\": vsync {1} -> {2}", title, this->vsync, vsync);
		this->vsync = vsync;
	}

	void GLFWRenderer::setWidth(int width) {
		glfwSetWindowSize(win, width, getHeight());
		PTOS_CORE_TRACE("GLFW WindowRenderer \{0}\": width {1} -> {2}", title, this->size.width, width);
		this->size.width = width;
	}

	void GLFWRenderer::setHeight(int height) {
		glfwSetWindowSize(win, getWidth(), height);
		PTOS_CORE_TRACE("GLFW WindowRenderer \{0}\": height {1} -> {2}", title, this->size.height, height);
		this->size.height = height;
	}

	void GLFWRenderer::setSize(const WindowSize& size) {
		glfwSetWindowSize(win, size.width, size.height);
		PTOS_CORE_TRACE("GLFW WindowRenderer \"{0}\": size ({1},{2}) -> ({3},{4})", title, this->size.width, this->size.height, size.width, size.height);
		this->size = size;
	}

	void GLFWRenderer::setTitle(const std::string& title) {
		glfwSetWindowTitle(win, title.c_str());
		PTOS_CORE_TRACE("GLFW WindowRenderer \"{0}\" -> \"{1}\"", this->title, title);
		this->title = title;
	}

	void GLFWRenderer::setIcon(GLFWimage& icon) {
		glfwSetWindowIcon(win, 1, &icon);
		PTOS_CORE_TRACE("GLFW WindowRenderer \"{0}\": icon {1}B ({2}x{3}) -> {4}B ({5}x{6})", title,
			this->icon.width * this->icon.height, this->icon.width, this->icon.height,
			icon.width * icon.height, icon.width, icon.height);
		this->icon = icon;
	}

	void GLFWRenderer::update() {
		glfwPollEvents();
		glfwSwapBuffers(win);
		eventLayer->dispatch(new WindowEvent(WINDOW_UPDATE, this));
	}

	void GLFWRenderer::init(const WindowProperties& props) {
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

	void GLFWRenderer::shutdown() {
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

	void GLFWRenderer::create() {
		//init window with values stored in WindowRenderer
		win = glfwCreateWindow(size.width, size.height, title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(win);
		glfwSetWindowUserPointer(win, this);
		setVsync(VSYNC_DEFAULT);
		if (icon.width > 0 && icon.height > 0)
			glfwSetWindowIcon(win, 1, &icon);

		//set callbacks; dispatch events, change EventLayer state for appropriate events
		glfwSetWindowCloseCallback(win, [](GLFWwindow* window) {
			GLFWRenderer* renderer = (GLFWRenderer*)glfwGetWindowUserPointer(window);
			renderer->getEventLayer()->dispatch(new WindowEvent(WINDOW_CLOSE, renderer));

		});
		glfwSetWindowSizeCallback(win, [](GLFWwindow* window, int width, int height) {
			GLFWRenderer* renderer = (GLFWRenderer*)glfwGetWindowUserPointer(window);
			renderer->getEventLayer()->dispatch(new WindowEvent(WINDOW_RESIZE, renderer, width, height));

			WindowSize size;
			size.width = width;
			size.height = height;
			renderer->setSize(size);
		});
		glfwSetWindowPosCallback(win, [](GLFWwindow* window, int xpos, int ypos) {
			GLFWRenderer* renderer = (GLFWRenderer*)glfwGetWindowUserPointer(window);
			renderer->getEventLayer()->dispatch(new WindowEvent(WINDOW_MOVE, renderer, xpos, ypos));
		});
		glfwSetKeyCallback(win, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			GLFWRenderer* renderer = (GLFWRenderer*)glfwGetWindowUserPointer(window);

			WindowEventType type;
			if (action == GLFW_PRESS)
				type = WINDOW_KEY_DOWN;
			else if (action == GLFW_RELEASE)
				type = WINDOW_KEY_UP;
			else
				return;

			renderer->getEventLayer()->dispatch(new WindowEvent(type, renderer, key));
		});
		glfwSetMouseButtonCallback(win, [](GLFWwindow* window, int button, int action, int mods) {
			GLFWRenderer* renderer = (GLFWRenderer*)glfwGetWindowUserPointer(window);

			WindowEventType type;
			if (action == GLFW_PRESS)
				type = WINDOW_MOUSE_DOWN;
			else if (action == GLFW_RELEASE)
				type = WINDOW_MOUSE_UP;
			else
				return;

			renderer->getEventLayer()->dispatch(new WindowEvent(type, renderer, button));
		});
		glfwSetScrollCallback(win, [](GLFWwindow* window, double xoffset, double yoffset) {
			GLFWRenderer* renderer = (GLFWRenderer*)glfwGetWindowUserPointer(window);
			renderer->getEventLayer()->dispatch(new WindowEvent(WINDOW_MOUSE_SCROLL, renderer, xoffset, yoffset));
		});
		glfwSetCursorPosCallback(win, [](GLFWwindow* window, double xpos, double ypos) {
			GLFWRenderer* renderer = (GLFWRenderer*)glfwGetWindowUserPointer(window);
			PTOS_CORE_DEBUG("{0},{1}", xpos, ypos);
			renderer->getEventLayer()->dispatch(new WindowEvent(WINDOW_MOUSE_MOVE, renderer, xpos, ypos));
		});
		PTOS_CORE_INFO("GLFW WindowRenderer \"{0}\" created", title);
	}

	void GLFWRenderer::destroy() {
		glfwDestroyWindow(win);
		win = nullptr;
		PTOS_CORE_INFO("GLFW WindowRenderer \"{0}\" destroyed", title);
	}
}
