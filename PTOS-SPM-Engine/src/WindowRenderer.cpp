#include <iostream>

#include "Log.h"
#include "WindowRenderer.h"

static void glfwErrorCallback(int code, const char* description) {
	PTOS_CORE_ERR("GLFW Error [{0}]: {1}", code, description);
}

namespace PTOS {

	static const bool VSYNC_DEFAULT = true;
	static const int VSYNC_INTERVAL = 1; //TODO figure out an actual value to set this to
	static bool initializedGLFW = false;

	WindowRenderer::WindowRenderer(/* TODO EventLayer* eventLayer */) {
		vsync = VSYNC_DEFAULT;
	}

	//GLFW Renderer

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

	void GLFWRenderer::update() {
		glfwPollEvents();
		glfwSwapBuffers(win);
		//PTOS_CORE_TRACE("GLFW WindowRenderer \"{0}\": update") //would be too annoying
		//TODO dispatch update event
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
			PTOS_CORE_TRACE("Initialized GLWF");
			initializedGLFW = true;
			glfwSetErrorCallback(glfwErrorCallback);
		}

		PTOS_CORE_INFO("Initialized GLFW WindowRenderer \"{0}\": ({1}, {2})", title, size.width, size.height);
	}

	void GLFWRenderer::shutdown() {
		if (!isInitialized || isShutdown) return;
		isShutdown = true;
		destroy();
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
			//TODO dispatch event (windowcontrol)
			PTOS_CORE_DEBUG("Pressed Close Button");
		});
		glfwSetWindowSizeCallback(win, [](GLFWwindow* window, int width, int height) {
			GLFWRenderer* renderer = (GLFWRenderer*)glfwGetWindowUserPointer(window);
			//TODO dispatch event (windowtransform)
			WindowSize size;
			size.width = width;
			size.height = height;
			renderer->setSize(size);
		});
		glfwSetWindowPosCallback(win, [](GLFWwindow* window, int xpos, int ypos) {
			//TODO dispatch event (windowtransform)
		});
		glfwSetKeyCallback(win, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			//TODO dispatch event (key)
			switch (action) {
			case GLFW_PRESS:
				break;
			case GLFW_RELEASE:
				break;
			case GLFW_REPEAT:
				break;
			}
		});
		glfwSetMouseButtonCallback(win, [](GLFWwindow* window, int button, int action, int mods) {
			//TODO dispatch event (mouse)
			switch (action) {
			case GLFW_PRESS:
				break;
			case GLFW_RELEASE:
				break;
			}
		});
		glfwSetScrollCallback(win, [](GLFWwindow* window, double xoffset, double yoffset) {
			//TODO dispatch event (mouse)
		});
		glfwSetCursorPosCallback(win, [](GLFWwindow* window, double xpos, double ypos) {
			//TODO dispatch event (mouse)
		});
		PTOS_CORE_INFO("GLFW WindowRenderer \"{0}\" created", title);
	}

	void GLFWRenderer::destroy() {
		glfwDestroyWindow(win);
		win = nullptr;
		PTOS_CORE_INFO("GLFW WindowRenderer \"{0}\" destroyed", title);
	}
}

std::ostream& operator<< (std::ostream& out, PTOS::WindowRenderer& renderer) {
	return out << "<" << renderer.getRendererName() << "\"" << renderer.getTitle()
		<< "\" (" << renderer.getWidth() << "x" << renderer.getHeight() << ") at "
		<< &renderer << ">";
}