#pragma once

#include "resources/shader.hpp"
#include "resources/mesh.hpp"

#include "core/math/math.hpp"

namespace LowRenderer
{
	class Model
	{
	private:
		Shader*		shader;
		Mesh*		mesh;

	public:
		Model();
		~Model();

		//view projection matrix as argument (model matrix is automatically used with mesh)
		void draw(const mat4& VP) const;
	};
}

using namespace LowRenderer;