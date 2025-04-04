
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

std::string colorPixelSrc = R"(

#version 330 core

layout(location = 0) out vec4 color;
uniform vec3 _color;

void main()
{
	color = vec4(_color, 1.0);
}
)";

std::string vertexSrc = R"(

#version 330 core

layout(location = 0) in vec3 _position;
layout(location = 1) in vec4 _color;

uniform mat4 viewProjection;
uniform mat4 transform;

out vec4 vcolor;
			
void main()
{
	vcolor = _color;
	gl_Position = viewProjection * transform * vec4(_position, 1.0);

}
)";


//App Code


PTOS::Application* App = nullptr;
PTOS::EventLayer* gameLayer = nullptr;
PTOS::Window* mainWindow = nullptr;

PTOS::SceneInfo scene;
PTOS::SceneItem triangle;
PTOS::SceneItem square;
PTOS::GLFWVertexBuffer triangleBuffer;
PTOS::GLFWVertexBuffer squareBuffer;
PTOS::GLFWIndexBuffer triangleIndexBuffer;
PTOS::GLFWIndexBuffer squareIndexBuffer;

//generate arrays and buffers
void initVisualData(PTOS::WindowRenderer* windowRenderer) {

	windowRenderer->bind();

	square.vertexArray = new PTOS::GLFWVertexArray();
	square.vertexArray->create();
	square.vertexArray->bind();

	float squarePPs[4 * 3] = {
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};

	squareBuffer.create(squarePPs, sizeof(squarePPs));

	PTOS::BufferLayout squareLayout = {
		{ PTOS::BuffElmType::FLOAT(3), "_position" }
	};
	squareBuffer.setLayout(squareLayout);
	square.vertexArray->addVertexBuffer(&squareBuffer);

	unsigned int squareIndecies[6] = { 0, 1, 2, 2, 3, 0};
	squareIndexBuffer.create(squareIndecies, sizeof(squareIndecies));
	square.vertexArray->setIndexBuffer(&squareIndexBuffer);

	triangle.vertexArray = new PTOS::GLFWVertexArray();

	triangle.vertexArray->create();
	triangle.vertexArray->bind();

	float trianglePPs[3 * 7] = {
	   -0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
	};

	triangleBuffer.create(trianglePPs, sizeof(trianglePPs));

	PTOS::BufferLayout triangleLayout = {
		{ PTOS::BuffElmType::FLOAT(3), "_position" },
		{ PTOS::BuffElmType::FLOAT(4), "_color" }
	};
	triangleBuffer.setLayout(triangleLayout);
	triangle.vertexArray->addVertexBuffer(&triangleBuffer);

	unsigned int triangleIndecies[3] = { 0, 1, 2 };
	triangleIndexBuffer.create(triangleIndecies, sizeof(triangleIndecies));
	triangle.vertexArray->setIndexBuffer(&triangleIndexBuffer);

	std::string triangleSrc[] = { vertexSrc, pixelSrc };
	std::string squareSrc[] = { vertexSrc, colorPixelSrc };
	int types[] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };

	square.shader = PTOS::GLFWShader::compile(squareSrc, types, sizeof(squareSrc) / sizeof(squareSrc[0]));

	triangle.shader = PTOS::GLFWShader::compile(triangleSrc, types, sizeof(triangleSrc) / sizeof(triangleSrc[0]));
	square.transform = new PTOS::ComponentTransform();
	triangle.transform = new PTOS::ComponentTransform();

	scene.addSceneItem(&square);
	scene.addSceneItem(&triangle);
}


PTOS::EventResult onAppStart(const PTOS::EventContext& ctx) {
	PTOS::GLFWWindowRenderer* glfwren = new PTOS::GLFWWindowRenderer(EVENTS, PTOS::EventLayers::WINDOW);

	mainWindow = App->newWindow(800, 450, "Test Window", nullptr, glfwren, new PTOS::GLFWRenderer());
	glfwren->setVsync(false);

	float aw, ah;
	if (mainWindow->getWidth() > mainWindow->getHeight()) {
		aw = 1;
		ah = (float)mainWindow->getHeight() / mainWindow->getWidth();
	}
	else {
		aw = (float)mainWindow->getWidth() / mainWindow->getHeight();
		ah = 1;
	}
	scene.camera = new PTOS::Camera2D(-ah, ah, -aw, aw);

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
	float dt = event->windowRenderer->getDeltaTime();

	if (event->windowRenderer != mainWindow->getWindowRenderer())
		return {};

	if (input.getHold(PTOS::Inputs::CODE_KEY_W))
		scene.camera->setPosition(scene.camera->getPosition() + PTOS::vec3( 0, 1, 0 ) * dt);
	if (input.getHold(PTOS::Inputs::CODE_KEY_A))
		scene.camera->setPosition(scene.camera->getPosition() + PTOS::vec3(-1, 0, 0) * dt);
	if (input.getHold(PTOS::Inputs::CODE_KEY_S))
		scene.camera->setPosition(scene.camera->getPosition() + PTOS::vec3(0, -1, 0) * dt);
	if (input.getHold(PTOS::Inputs::CODE_KEY_D))
		scene.camera->setPosition(scene.camera->getPosition() + PTOS::vec3(1, 0, 0) * dt);
	if (input.getDown(PTOS::Inputs::CODE_KEY_Q))
		scene.camera->setRotationDegrees(scene.camera->getRotationDegrees() + 45); //CCW is +
	if (input.getDown(PTOS::Inputs::CODE_KEY_E))
		scene.camera->setRotationDegrees(scene.camera->getRotationDegrees() - 45); //CW is -

	float x = 0, y = 0;
	if (input.getHold(PTOS::Inputs::CODE_KEY_KP_UP))
		y += dt;
	if (input.getHold(PTOS::Inputs::CODE_KEY_KP_LEFT))
		x -= dt;
	if (input.getHold(PTOS::Inputs::CODE_KEY_KP_RIGHT))
		x += dt;
	if (input.getHold(PTOS::Inputs::CODE_KEY_KP_DOWN))
		y -= dt;

	if (x || y)
		triangle.transform->changePostion(PTOS::vec3(x, y, 0));

	if (input.getDown(PTOS::Inputs::CODE_KEY_X)) {
		scene.camera->setPosition(PTOS::vec3(0, 0, 0));
		scene.camera->setRotation(0);
		triangle.transform->setPosition(PTOS::vec3(0, 0, 0));
	}

	square.shader->bind();
	square.shader->upload("_color", PTOS::vec3(0, 1.0f, 0));

	for (auto& pair : input.getAnyAll()) {
		PTOS_DEBUG("{0}: {1}", (int)pair.first, pair.second.count);
	}

	PTOS_DEBUG("{0}s", dt);

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
	*scene.camera = PTOS::Camera2D(-ah, ah, -aw, aw);
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
	gameLayer->addListener(PTOS::EventTypes::WINDOW_RESIZE, onWindowResize);

}