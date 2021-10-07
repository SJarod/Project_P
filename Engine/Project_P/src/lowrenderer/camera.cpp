#include "lowrenderer/camera.hpp"

mat4 LowRenderer::Camera::frustum(const float& left, const float& right, const float& bot, const float& top, bool orthographic) const
{
	if (orthographic)
	{
		mat4 temp;
		temp.c[0] = { 2 / (right - left), 0.f, 0.f, -(right + left) / (right - left) };
		temp.c[1] = { 0.f, 2 / (top - bot), 0.f, -(top + bot) / (top - bot) };
		temp.c[2] = { 0.f, 0.f, -2 / (far - near), -(far + near) / (far - near) };
		temp.c[3] = { 0.f, 0.f, 0.f, 1.f };
		return temp;
	}

	mat4 temp;
	temp.c[0] = { (2 * near) / (right - left), 0.f, 0.f, -near * (right + left) / (right - left) };
	temp.c[1] = { 0.f, (2 * near) / (top - bot), 0.f, -near * (top + bot) / (top - bot) };
	temp.c[2] = { 0.f, 0.f, -(far + near) / (far - near), -(2 * far * near) / (far - near) };
	temp.c[3] = { 0.f, 0.f, -1.f, 0.f };
	return temp;
}

LowRenderer::Camera::Camera(const float& aspectRatio)
{
	aspect = aspectRatio;
}

void LowRenderer::Camera::update(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwGetCursorPos(window, &m_mouseX, &m_mouseY);

	position.x += (glfwGetKey(window, GLFW_KEY_D) - glfwGetKey(window, GLFW_KEY_A)) * moveSpeed * cosf(yaw * TORAD) +
				  (glfwGetKey(window, GLFW_KEY_S) - glfwGetKey(window, GLFW_KEY_W)) * moveSpeed * sinf(yaw * TORAD);
	position.z += (glfwGetKey(window, GLFW_KEY_S) - glfwGetKey(window, GLFW_KEY_W)) * moveSpeed * cosf(yaw * TORAD) -
				  (glfwGetKey(window, GLFW_KEY_D) - glfwGetKey(window, GLFW_KEY_A)) * moveSpeed * sinf(yaw * TORAD);

	position.y += (glfwGetKey(window, GLFW_KEY_SPACE) - glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) * moveSpeed;

	yaw -= (float)(m_mouseX - m_oldX) * mouseSensitivity;
	pitch += (float)(m_mouseY - m_oldY) * mouseSensitivity;
	clamp(pitch, -90.f, 90.f);

	m_oldY = (float)m_mouseY;
	m_oldX = (float)m_mouseX;
}

mat4 LowRenderer::Camera::getViewMatrix() const
{
	return rotateXMatrix(pitch) * rotateYMatrix(-yaw) * translateMatrix(-position);
}

mat4 LowRenderer::Camera::getProjMatrix() const
{
	float top = near * tanf(fovY * TORAD * 0.5f);
	float right = top * aspect;

	return frustum(-right, right, -top, top, false);
}

mat4 LowRenderer::Camera::getOrthMatrix() const
{
	float top = tanf(fovY * TORAD * 0.5f);
	float right = top * aspect;

	return frustum(-right, right, -top, top, true);
}

mat4 LowRenderer::Camera::getPerspective(const bool orthographic) const
{
	if (orthographic)
		return getOrthMatrix();
	return getProjMatrix();
}

mat4 LowRenderer::Camera::getVPMatrix() const
{
	return getPerspective(false) * getViewMatrix();
}

mat4 LowRenderer::Camera::getMVPMatrix(const mat4& modelMatrix) const
{
	return getPerspective(false) * getViewMatrix() * modelMatrix;
}