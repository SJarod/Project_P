#pragma once

#include "physics/transform.hpp"

namespace Interface
{
	class ObjectI
	{
	public:
		virtual ~ObjectI() = default;

		Transform transform;

		virtual void start() = 0;
		virtual void update() = 0;
		virtual void fixedUpdate() {};

		//certain objects such as GameObjects need rendering
		virtual void render() {};
	};
}