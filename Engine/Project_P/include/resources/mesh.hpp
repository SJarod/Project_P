#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "physics/transform.hpp"

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

		Mesh();
		~Mesh();

		void render() const;
	};
}

using namespace Resources;