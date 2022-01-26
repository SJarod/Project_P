#pragma once

#include <vector>

#include "physics/transform.hpp"

namespace Resources
{
	class Vertex
	{
	public:
		vec3 pos;	//vertex position
		vec2 uv;	//texture coordinates
		vec3 n;		//vertex normal
	};

	struct GPUMesh {};

	class Mesh
	{
	public:
		//cpu side
		std::vector<Vertex> vertices;
		//gpu side
		GPUMesh* gpu;

	public:
		Transform transform;
	};
}

using namespace Resources;