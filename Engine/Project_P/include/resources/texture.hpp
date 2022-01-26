#pragma once

namespace Resources
{
	struct GPUTexture {};

	struct TextureDim
	{
		int width;
		int height;
	};

	class Texture
	{
	public:
		//cpu side
		unsigned char*	data;
		TextureDim		dim;
		//gpu side
		GPUTexture* gpu;
	};
}

using namespace Resources;