#pragma once

#include "predefines.h"
#include "ptosmath.h"

namespace PTOS {

	class ComponentTransform {
	public:
		ComponentTransform();
		~ComponentTransform();

		inline const vec3& getPosition() const { return p; }
		inline const vec3& getRotation() const { return r; }
		inline const vec3& getScale() const { return s; }
		inline const mat4& getMatrix() const { return *cachedTransform; }

		inline void setPosition(const vec3& postion) { this->p = postion; uptodate = false; }
		inline void setRotation(const vec3& rotation) {
			this->r = rotation;
			uptodate = false;
			isrotated = rotation[0] || rotation[1] || rotation[2];
		}
		inline void setScale(const vec3& scale) { this->s = scale; uptodate = false; }

		inline const vec3& changePostion(const vec3& delta) { setPosition(p + delta); return p; }
		inline const vec3& changeRotation(const vec3& delta) { setRotation(r + delta); return r; }
		inline const vec3& changeScale(const vec3& delta) { setScale(s + delta); return s; }
		inline const vec3& changeScale(float factor) { setScale(s * factor); return s; }

		void calcMatrix();

	private:
		vec3 p = vec3(0, 0, 0);	//position
		vec3 r = vec3(0, 0, 0);	//rotation
		vec3 s = vec3(1, 1, 1);	//scale
		mat4* cachedTransform = nullptr;
		bool uptodate = false;
		bool isrotated = false;
	};
}