
//DEBUG
#include "glad/glad.h"

#include "PTOS.h"
#include <iostream>

//Shaders

std::string pixelSrc = R"(

#version 330 core

layout(location = 0) out vec4 color;

in vec4 vcolor;
			
void main()
{
	color = vcolor;
}
)";

std::string vertexSrc = R"(

#version 330 core

layout(location = 0) in vec3 _position;
layout(location = 1) in vec4 _color;

uniform mat4 viewProjection;

out vec4 vcolor;
			
void main()
{
	vcolor = _color;
	gl_Position = viewProjection * vec4(_position, 1.0);

}
)";


//App Code


PTOS::Application* App = nullptr;
PTOS::EventLayer* gameLayer = nullptr;
PTOS::Window* mainWindow = nullptr;

PTOS::SceneInfo scene;
PTOS::GLFWVertexBuffer vertexBuffer;
PTOS::GLFWIndexBuffer indexBuffer;

//generate arrays and buffers
void initVisualData(PTOS::WindowRenderer* windowRenderer) {

	windowRenderer->bind();

	scene.vertexArray = new PTOS::GLFWVertexArray();

	scene.vertexArray->create();
	scene.vertexArray->bind();

	float pps[3 * 7] = {
	   -0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
	};

	vertexBuffer.create((float*)pps, sizeof(pps));

	PTOS::BufferLayout layout = {
		{ PTOS::BuffElmType::FLOAT(3), "_position" },
		{ PTOS::BuffElmType::FLOAT(4), "_color" }
	};
	vertexBuffer.setLayout(layout);
	scene.vertexArray->addVertexBuffer(&vertexBuffer);

	unsigned int indecies[3] = { 0, 1, 2 };
	indexBuffer.create(indecies, sizeof(indecies));
	scene.vertexArray->setIndexBuffer(&indexBuffer);

	std::string src[] = { vertexSrc, pixelSrc };
	int types[] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };

	scene.shader = PTOS::GLFWShader::compile(src, types, sizeof(src) / sizeof(src[0]));
}


PTOS::EventResult onAppStart(const PTOS::EventContext& ctx) {
	PTOS::GLFWWindowRenderer* glfwren = new PTOS::GLFWWindowRenderer(EVENTS, PTOS::EventLayers::WINDOW);

	mainWindow = App->newWindow(800, 450, "Test Window", nullptr, glfwren, new PTOS::GLFWRenderer());
	//mainWindow->setFramerate(60);

	float aw, ah;
	if (mainWindow->getWidth() > mainWindow->getHeight()) {
		aw = 1;
		ah = (float)mainWindow->getHeight() / mainWindow->getWidth();
	}
	else {
		aw = (float)mainWindow->getWidth() / mainWindow->getHeight();
		ah = 1;
	}
	scene.camera = new PTOS::Camera2D(-aw, aw, -ah, ah);

	mainWindow->setScene(&scene);

	mainWindow->open();
	initVisualData(glfwren);

	//glfwren->camera.setPosition({ -0.5, 0, 0 });
	//glfwren->camera.setRotationDegrees(45);
	return {};
}

PTOS::EventResult onAppEnd(const PTOS::EventContext& ctx) {
	App = nullptr;
	return {};
}

PTOS::EventResult onWindowUpdate(const PTOS::EventContext& ctx) {
	PTOS::WindowEvent* event = (PTOS::WindowEvent*)ctx.event.data;
	PTOS::Input input(event->windowRenderer);

	if (event->windowRenderer != mainWindow->getWindowRenderer())
		return {};

	if (input.getHold(PTOS::Inputs::CODE_KEY_W))
		scene.camera->setPosition(scene.camera->getPosition() + PTOS::vec3( 0, 1, 0 ) / 60.0f);
	if (input.getHold(PTOS::Inputs::CODE_KEY_A))
		scene.camera->setPosition(scene.camera->getPosition() + PTOS::vec3(-1, 0, 0) / 60.0f);
	if (input.getHold(PTOS::Inputs::CODE_KEY_S))
		scene.camera->setPosition(scene.camera->getPosition() + PTOS::vec3(0, -1, 0) / 60.0f);
	if (input.getHold(PTOS::Inputs::CODE_KEY_D))
		scene.camera->setPosition(scene.camera->getPosition() + PTOS::vec3(1, 0, 0) / 60.0f);
	if (input.getDown(PTOS::Inputs::CODE_KEY_Q))
		scene.camera->setRotationDegrees(scene.camera->getRotationDegrees() + 45); //CCW is +
	if (input.getDown(PTOS::Inputs::CODE_KEY_E))
		scene.camera->setRotationDegrees(scene.camera->getRotationDegrees() - 45); //CW is -

	if (input.getDown(PTOS::Inputs::CODE_KEY_X)) {
		scene.camera->setPosition({ 0, 0, 0 });
		scene.camera->setRotation(0);
	}

	for (auto& pair : input.getAnyAll()) {
		PTOS_DEBUG("{0}: {1}", (int)pair.first, pair.second.count);
	}

	return {};
}

PTOS::EventResult onWindowClose(const PTOS::EventContext& ctx) {
	PTOS::WindowEvent* event = (PTOS::WindowEvent*)ctx.event.data;
	event->windowRenderer->shutdown(); //perma-close window

	//if window closed was the main window, then stop the app

	if (event->windowRenderer == mainWindow->getWindowRenderer())
		App->stop();
	App->removeWindow(event->windowRenderer);

	return { true, true, true };
}

PTOS::EventResult onWindowResize(const PTOS::EventContext& ctx) {
	PTOS::WindowEvent* event = (PTOS::WindowEvent*)ctx.event.data;
	float aw, ah;
	if (event->dx > event->dy) {
		aw = 1;
		ah = event->dy / event->dx;
	}
	else {
		aw = event->dx / event->dy;
		ah = 1;
	}
	*scene.camera = PTOS::Camera2D(-aw, aw, -ah, ah);
	return {};
}

void PTOSInit(PTOS::Application* app) {
	App = app;

	gameLayer = new PTOS::EventLayer();
	EVENTS->addLayer(gameLayer);

	gameLayer->addListener(PTOS::EventTypes::APP_START, onAppStart);
	gameLayer->addListener(PTOS::EventTypes::APP_END, onAppEnd);
	gameLayer->addListener(PTOS::EventTypes::WINDOW_UPDATE, onWindowUpdate);
	gameLayer->addListener(PTOS::EventTypes::WINDOW_CLOSE, onWindowClose);

}