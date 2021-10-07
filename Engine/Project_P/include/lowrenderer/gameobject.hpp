#pragma once

#include "lowrenderer/model.hpp"

#include "core/math/math.hpp"

namespace LowRenderer
{
	class GameObject
	{
	private:
		Model model;

	public:
		void draw(const mat4& VP) const;
	};
}

using namespace LowRenderer;