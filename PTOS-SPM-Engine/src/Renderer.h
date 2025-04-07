#pragma once

#include "predefines.h"
#include "ptosmath.h"

#include "Camera.h"
#include "ComponentTransform.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

#include <vector>
#include <unordered_map>

namespace PTOS {
	
	// takes 4 hex vales (rgba) and stores them as percents (x / 0xff) in a vec4
	inline rgba rgbaHexToP(float r, float g, float b, float a = 0xff) { return rgba(r / 0xff, g / 0xff, b / 0xff, a / 0xff); }


	namespace Renderers {
		enum RendererName {
			GL
		};
	}

#ifdef PTOS_RENDER_DYNAMIC
	extern Renderers::RendererName CURRENT_RENDERER;
#endif


	class SceneInfo {
	public:
		SceneInfo();
		SceneInfo(Camera2D* camera);
		~SceneInfo();

		inline const std::vector<SceneItem*>& getItems() const { return items; }
		inline SceneItem* getItem(size_t index) const { return items[index]; }

		void addSceneItem(SceneItem* item);
		void removeSceneItem(size_t index);
		void removeSceneItem(SceneItem* item);

		Camera2D* camera;
		bool overrideVPCache = true;

	private:
		std::vector<SceneItem*> items;
	};

	struct SceneItem {
		Shader* shader = nullptr;
		VertexArray* vertexArray = nullptr;
		ComponentTransform* transform = nullptr;
		Texture* texture = nullptr;
	};

	class Renderer {
	public:
		void submit(SceneInfo* scene, SceneItem* item);
		void submit(SceneInfo* scene);

		virtual void init() = 0;
		virtual void setClearColor(const rgba& color) = 0;
		virtual void clear() = 0;
		virtual void drawIndexed(VertexArray* vertexArray) = 0;
	};
}