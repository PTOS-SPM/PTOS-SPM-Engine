#include "Camera.h"
#include "transform.h"


namespace PTOS {

	Camera2D::Camera2D(const mat4& projection) {
		this->projection = projection;
		vp = projection * view;
	}

	Camera2D::Camera2D(float left, float right, float bottom, float top, float near, float far)
		: Camera2D(ortho(left, right, bottom, top, near, far)) {}



	bool Camera2D::recalc() {
		if (calced)
			return false;

		view = translate(rotate(PTOS_MAT4_IDENTITY, rotation, vec3(0, 0, 1.0f)), position);
		vp = inverse(projection * view);
		calced = true;
		return true;
	}
}
