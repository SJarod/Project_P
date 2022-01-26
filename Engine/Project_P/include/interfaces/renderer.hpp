#pragma once

#include "resources/mesh.hpp"
#include "resources/texture.hpp"
#include "resources/material.hpp"

namespace Interface
{
	class RendererI
	{
	public:
		virtual ~RendererI() = default;

		virtual void render() = 0;

		virtual GPUMesh* generateGPUMesh(const Mesh& mesh) = 0;
		virtual GPUTexture* generateGPUTexture(const Texture& tex) = 0;
		virtual GPUMaterial* generateGPUMaterial(const Material& mat) = 0;
	};
}