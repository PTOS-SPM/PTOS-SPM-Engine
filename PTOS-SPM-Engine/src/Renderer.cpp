#include "Renderer.h"

namespace PTOS {
	SceneInfo::~SceneInfo() {
		delete camera;
		delete shader;
		delete vertexArray;
	}

	void Renderer::submit(SceneInfo* scene) {
		if (scene->camera->recalc()) {
			scene->shader->bind();
			scene->shader->upload("viewProjection", scene->camera->getVP());
		}
		drawIndexed(scene->vertexArray);
	}
}
