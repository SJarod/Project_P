#pragma once

namespace Resources
{
	struct GPUMaterial {};

	class Material
	{
	public:
		//cpu side
		//gpu side
		GPUMaterial* gpu;
	};
}

using namespace Resources;