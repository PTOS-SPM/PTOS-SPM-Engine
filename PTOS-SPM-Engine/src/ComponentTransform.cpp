#include "ComponentTransform.h"

namespace PTOS {
	ComponentTransform::ComponentTransform() {
		cachedTransform = new PTOS_MAT4_IDENTITY;
	}

	ComponentTransform::~ComponentTransform() {
		delete cachedTransform;
	}

	void ComponentTransform::calcMatrix() {
		if (uptodate)
			return;
		mat4 t = scale(PTOS_MAT4_IDENTITY, s);
		if (isrotated) //will result in NaNs for glm if 0 rotation
			t = rotate(t, 1.0f, r);
		t = translate(t, p);
		*cachedTransform = t;
		uptodate = true;
	}
}