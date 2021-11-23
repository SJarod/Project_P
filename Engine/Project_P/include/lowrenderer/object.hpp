#pragma once

#include "physics/transform.hpp"

namespace LowRenderer
{
	class Object
	{
	protected:
		Transform transform;

		virtual void start();
		virtual void update();
		virtual void fixedUpdate();
	};
}

using namespace LowRenderer;