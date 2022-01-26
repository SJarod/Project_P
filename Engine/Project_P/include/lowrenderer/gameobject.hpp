#pragma once

#include "lowrenderer/object.hpp"
#include "lowrenderer/model.hpp"

#include "math/math.hpp"

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