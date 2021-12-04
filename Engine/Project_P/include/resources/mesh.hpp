#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "physics/transform.hpp"

#include "physics/primitives3/box.hpp"
#include "physics/primitives3/sphere.hpp"

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
		std::vector<float>			vertices;
		//std::vector<Vertex>			vertices;
		std::vector<unsigned int>	indices;

		GLuint		VAO;

		void generateMesh();

	public:
		Transform	transform;

		~Mesh();

		bool loadMesh(const char* filename);
		bool loadMesh(Box* b);
		bool loadMesh(Sphere* sph);

		void render() const;
	};
}

using namespace Resources;