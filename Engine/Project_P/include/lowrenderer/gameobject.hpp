#pragma once

#include "math/math.hpp"

#include "lowrenderer/object.hpp"
#include "lowrenderer/model.hpp"

namespace LowRenderer
{
	class GameObject : public Object
	{
	private:
		Model model;

	public:
		virtual void start() override;
		virtual void update() override;
		virtual void render() override;
	};
}

using namespace LowRenderer;