#pragma once

#include "predefines.h"
#include "ptosmath.h"


namespace PTOS {
	class Camera2D {
	public:
		Camera2D(const mat4& projection);
		Camera2D(float left, float right, float bottom, float top, float near=-1.0f, float far=1.0f);
		Camera2D() : Camera2D(-1.0, 1.0, -1.0, 1.0) {}

		inline const vec3& getPosition() const { return position; }
		inline float getRotation() const { return rotation; }
		inline float getRotationDegrees() const { return degrees(rotation); }
		inline const mat4& getProjection() const { return projection; }
		inline const mat4& getView() const { return view; }
		inline const mat4& getVP() const { return vp; }

		//Set the camera's projection matrix
		inline void setProjection(const mat4& projection);
		//Set the camera's projection matrix to the given matrix
		inline void setProjection(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0f);
		//Set the camera's position
		inline void setPosition(const vec3& position) { this->position = position; calced = false; }
		//Set the camera's rotation in degrees
		inline void setRotationDegrees(float rotation) { this->rotation = radians(rotation); calced = false; }
		//Set the camera's rotation in radians
		inline void setRotation(float rotation) { this->rotation = rotation; calced = false; }

		bool recalc();

	private:
		mat4 view = mat4({ { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } });
		mat4 projection;
		mat4 vp;


		bool calced = false;

		vec3 position = vec3(0,0,0);
		float rotation = 0;
	};
}
