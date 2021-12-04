#pragma once

#include "resources/shader.hpp"
#include "resources/mesh.hpp"
#include "lowrenderer/camera.hpp"

#include "core/math/math.hpp"

namespace LowRenderer
{
	class Model
	{
	private:
		Shader*		shader;
		Mesh*		mesh;

		Camera*		renderCam = nullptr;

	public:
		Model();
		~Model();

		//view projection matrix as argument (model matrix is automatically used with mesh)
		void draw() const;
	};
}

using namespace LowRenderer;