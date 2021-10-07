#pragma once

#include "core/math/math.hpp"
#include "core/math/quaternion.hpp"

namespace Physics
{
	class Referential3
	{
	public:
		vec3 origin;
		vec3 i, j, k;

		Referential3() = default;
		Referential3(const vec3& origin);

		void rotate(const Quaternion& q);
	};
}

using namespace Physics;