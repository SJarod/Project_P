#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Resources
{
	class Texture
	{
	private:
		GLuint data;

	public:
		bool loadTexture(const std::string& filename);

		void bindTexture() const;
	};
}

using namespace Resources;