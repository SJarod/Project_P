#pragma once

#include "lowrenderer/model.hpp"

#include "core/math/math.hpp"

#include "lowrenderer/object.hpp"

namespace LowRenderer
{
	class GameObject : public Object
	{
	private:
		Model model;

	public:
		void draw(const mat4& VP) const;
	};
}

using namespace LowRenderer;