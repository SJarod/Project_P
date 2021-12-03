#pragma once

#include "core/math/math.hpp"

namespace Physics
{
	class Transform
	{
	public:
		vec3 position = { 0.f, 0.f, 0.f };
		vec3 rotation = { 0.f, 0.f, 0.f }; //pitch, yaw, roll
		vec3 scale = { 1.f, 1.f, 1.f };

		mat4 getModelMatrix() const;
	};
}

using namespace Physics;