#include "Renderer.h"

namespace PTOS {

#ifdef PTOS_RENDER_DYNAMIC
	PTOS_API Renderers::RendererName CURRENT_RENDERER = Renderers::GL;
#endif

	SceneInfo::SceneInfo() {
		camera = new Camera2D();
	}
	SceneInfo::SceneInfo(Camera2D* camera) {
		this->camera = camera;
	}
	SceneInfo::~SceneInfo() {
		if (camera != nullptr) {
			delete camera;
			camera = nullptr;
		}
	}

	void SceneInfo::addSceneItem(SceneItem* item) {
		items.push_back(item);
		overrideVPCache = true;
	}

	void SceneInfo::removeSceneItem(size_t index) {
		SceneItem* item = items[index];
		items.erase(items.begin() + index);
		overrideVPCache = true;
	}

	void SceneInfo::removeSceneItem(SceneItem* item) {
		bool modified = false;
		for (auto it = items.begin(); it != items.end();) {
			if (*it == item) {
				items.erase(it);
				modified = true;
			}
			else it++;
		}

		if (modified)
			overrideVPCache = true;
	}

	void Renderer::submit(SceneInfo* scene, SceneItem* item) {
		if (scene->camera->recalc() || scene->overrideVPCache) {
			item->shader->bind();
			item->shader->upload("viewProjection", scene->camera->getVP());
		}
		if (item->transform != nullptr) {
			item->transform->calcMatrix();
			item->shader->upload("transform", item->transform->getMatrix());
		}
		if (item->texture != nullptr) {
			item->texture->bind();
			item->shader->upload("sampler", 0);
		}
		drawIndexed(item->vertexArray);
		scene->overrideVPCache = false;
	}

	void Renderer::submit(SceneInfo* scene) {
		bool updatedVP = scene->camera->recalc() || scene->overrideVPCache;
		const mat4& vp = scene->camera->getVP();
		for (auto it = scene->getItems().begin(); it != scene->getItems().end(); it++) {
			SceneItem* item = *it;
			item->shader->bind();
			if (updatedVP)
				item->shader->upload("viewProjection", vp);
			if (item->transform != nullptr) {
				item->transform->calcMatrix();
				item->shader->upload("transform", item->transform->getMatrix());
			}
			if (item->texture != nullptr) {
				item->texture->bind();
				drawIndexed(item->vertexArray);
				item->texture->unbind();
			} else drawIndexed(item->vertexArray);
		}
		scene->overrideVPCache = false;
	}
}
