#pragma once

#include "core/math/math.hpp"
#include "core/math/quaternion.hpp"

namespace Physics
{
	namespace Primitives3
	{
		class Capsule
		{
		public:
			vec3	center;
			float	height;
			float	radius;

			Quaternion q;

			Capsule() = default;
			Capsule(const vec3& center, const float& height, const float& radius, const Quaternion& q);
		};
	}
}

using namespace Physics::Primitives3;