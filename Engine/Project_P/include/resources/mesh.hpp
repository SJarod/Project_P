#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "physics/transform.hpp"

#include "physics/primitives3/box.hpp"
#include "physics/primitives3/sphere.hpp"

#include <string>

namespace Resources
{
	class Vertex
	{
	public:
		vec3 pos;	//vertex position
		vec2 uv;	//texture coordinates
		vec3 n;		//vertex normal
	};

	class Mesh
	{
	private:
		std::vector<Vertex> vertices;

		GLuint VAO;

		void assembleVertices(const std::vector<float3>& rawV,
						      const std::vector<uint3>&  rawI,
						      const std::vector<float2>& rawVt = std::vector<float2>(),
						      const std::vector<float3>& rawVn = std::vector<float3>());
		void generateMeshVAO();

	public:
		Transform transform;

		~Mesh();

		bool loadMesh(const std::string& filename);
		bool loadMesh(const Box& b);
		bool loadMesh(const Sphere& sph);

		void render() const;
	};
}

using namespace Resources;