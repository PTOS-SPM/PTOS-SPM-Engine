#include "Texture.h"

#ifdef PTOS_RENDER_DYNAMIC
#include "Log.h"
#include "Renderer.h"
#endif

#if defined(PTOS_RENDER_GL) || defined(PTOS_RENDER_DYNAMIC)
#include "GLFWTexture.h"
#endif

namespace PTOS {

	Texture2D* Texture2D::create(const std::string& path) {
#if defined(PTOS_RENDER_DYNAMIC)
		switch (CURRENT_RENDERER) {
		case Renderers::GL:
			return new GLFWTexture2D(path);
		default:
			PTOS_CORE_ASSERT(false, "Invalid renderer type");
		}
#elif defined(PTOS_RENDER_GL)
		return new GLFWTexture2D(path);
#endif
		return nullptr;
	}

}
