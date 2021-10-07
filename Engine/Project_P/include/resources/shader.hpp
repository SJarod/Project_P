#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "core/math/math.hpp"

namespace Resources
{
	class Shader
	{
	private:
		GLuint program = 0;

	public:
		Shader() = default;
		Shader(const std::string& shaderName);
		~Shader();

		void use() const; //use shader program

		void passBool(const bool& b, const char* name);	//pass bool uniform to shader
		void passFloat(const float& f, const char* name);	//pass float uniform to shader
		void passVec3(const vec3& v, const char* name);	//pass vec3 uniform to shader
		void passMat4(const mat4& m, const char* name);	//pass mat4 uniform to shader
	};
}

using namespace Resources;