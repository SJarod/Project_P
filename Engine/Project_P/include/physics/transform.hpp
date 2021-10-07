#pragma once

#include "core/math/math.hpp"

namespace Physics
{
	class Transform
	{
	private:
		vec3 m_position = { 0.f, 0.f, 0.f };
		vec3 m_rotation = { 0.f, 0.f, 0.f };
		vec3 m_scale = { 1.f, 1.f, 1.f };

	public:
		mat4 getModelMatrix() const;
	};
}

using namespace Physics;