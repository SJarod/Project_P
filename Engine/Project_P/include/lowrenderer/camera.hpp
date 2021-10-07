#pragma once

#include "core/math/math.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace LowRenderer
{
	class Camera
	{
	private:
		float	mouseSensitivity = 0.1f;
		float	moveSpeed = 1.f;
		double	m_mouseX = 0.f, m_mouseY = 0.f;
		float	m_oldX = 0.f, m_oldY = 0.f;

		float	pitch = 0.f;
		float	yaw = 0.f;

		//aspect ratio
		float	aspect = 16.f / 9.f;
		float	fovY = 75.f;

		float	near = 0.001f;
		float	far = 1000.f;

		vec3	position = { 0.f, 0.f, 0.f };

		mat4	frustum(const float& left, const float& right, const float& bot, const float& top, bool orthographic) const;

		mat4	getViewMatrix() const;

		//projection matrix (using frustum and 3D)
		mat4	getProjMatrix() const;
		//orthographic matrix
		mat4	getOrthMatrix() const;
		//choose perspective matrix
		mat4	getPerspective(const bool orthographic) const;

	public:
		Camera() = default;
		Camera(const float& aspectRatio);

		void	update(GLFWwindow* window);

		mat4	getVPMatrix() const;
		mat4	getMVPMatrix(const mat4& modelMatrix) const;
	};
}

using namespace LowRenderer;