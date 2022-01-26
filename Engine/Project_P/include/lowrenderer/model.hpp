#pragma once

#include "math/math.hpp"

#include "resources/mesh.hpp"
#include "resources/texture.hpp"
#include "lowrenderer/camera.hpp"

namespace LowRenderer
{
	class Model
	{
	private:
		Mesh*		mesh = nullptr;
		Texture*	texture = nullptr;

		Camera*		renderCam = nullptr;

	public:
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