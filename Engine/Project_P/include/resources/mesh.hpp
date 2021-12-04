#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "physics/transform.hpp"

#include "physics/primitives3/box.hpp"
#include "physics/primitives3/sphere.hpp"

namespace Resources
{
	class Mesh
	{
	private:
		std::vector<float>			vertices;
		std::vector<unsigned int>	indices;

		GLuint		VAO;

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