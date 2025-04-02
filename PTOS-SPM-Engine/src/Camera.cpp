#include "Camera.h"
#ifdef PTOS_GLM_MATH
#include "glm/gtc/matrix_transform.hpp"
#endif
#include "transform.h"


namespace PTOS {

	Camera2D::Camera2D(const mat4& projection) {
		this->projection = projection;
		vp = projection * view;
	}

	Camera2D::Camera2D(float left, float right, float bottom, float top, float near, float far)
#ifdef PTOS_GLM_MATH
		: Camera2D(glm::ortho(left, right, bottom, top, near, far)) {}
#else
		: Camera2D(projectionMatrix(left, right, bottom, top, near, far)) {}
#endif



	bool Camera2D::recalc() {
		if (calced)
			return false;

#ifdef PTOS_GLM_MATH
		view = glm::translate(glm::rotate(glm::mat4(1), rotation, glm::vec3(0, 0, 1.0f)), position);
		vp = glm::inverse(projection * view);
#else
		view = translate3(position) * rotate3(eulr(0.0, 0.0, rotation));
		vp = (projection * view).inverse();
#endif
		calced = true;
		return true;
	}
}
