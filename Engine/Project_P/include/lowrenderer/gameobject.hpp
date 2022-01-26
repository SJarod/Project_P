#pragma once

#include "math/math.hpp"

#include "interfaces/object.hpp"
#include "lowrenderer/model.hpp"

namespace LowRenderer
{
	class GameObject : public Interface::ObjectI
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