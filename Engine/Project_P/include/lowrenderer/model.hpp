#pragma once

#include "resources/shader.hpp"
#include "resources/mesh.hpp"
#include "resources/texture.hpp"
#include "lowrenderer/camera.hpp"

#include "math/math.hpp"

namespace LowRenderer
{
	class Model
	{
	private:
		Shader*		shader;
		Mesh*		mesh;
		Texture*	texture;

		Camera*		renderCam = nullptr;

	public:
		Model();
		~Model();

		inline void setRenderCam(Camera* cam);
		//view projection matrix as argument (model matrix is automatically used with mesh)
		void draw() const;
	};
}

using namespace LowRenderer;

inline void LowRenderer::Model::setRenderCam(Camera* cam)
{
	renderCam = cam;
}