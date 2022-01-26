#pragma once

#include "resources/shader.hpp"

#include "interfaces/renderer.hpp"

namespace LowRenderer
{
	class RendererBase : public Interface::RendererI
	{
	private:
		Shader* shader;

	public:
		RendererBase(const char* shader);
		~RendererBase() override;

		void render() override;

		GPUMesh* generateGPUMesh(const Mesh& mesh) override;
		GPUTexture* generateGPUTexture(const Texture& tex) override;
		GPUMaterial* generateGPUMaterial(const Material& mat) override;
	};
}

using namespace LowRenderer;