#pragma once

#include "physics/transform.hpp"

namespace LowRenderer
{
	class Object
	{
	public:
		virtual ~Object() = default;

		Transform transform;

		virtual void start();
		virtual void update();
		virtual void fixedUpdate();

		//certain objects such as GameObjects need rendering
		virtual void render();
	};
}

using namespace LowRenderer;