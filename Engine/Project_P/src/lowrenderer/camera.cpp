#include "lowrenderer/camera.hpp"

#include "core/engine/application.hpp"

#include <iostream>

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

LowRenderer::Camera::Camera()
{
	aspect = Application::getInstance()->getAspectRatio();
}

mat4 LowRenderer::Camera::getViewMatrix() const
{
	return rotateXMatrix(transform.rotation.x) * rotateYMatrix(-transform.rotation.y) * translateMatrix(-transform.position);
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

void LowRenderer::Camera::start()
{
	Object::start();

	GLFWwindow* window = Application::getInstance()->window;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwGetCursorPos(window, &mouseX, &mouseY);
	oldY = (float)mouseY;
	oldX = (float)mouseX;
}

void LowRenderer::Camera::update()
{
	Object::update();

	GLFWwindow* window = Application::getInstance()->window;

	float& pitch = transform.rotation.x;
	float& yaw = transform.rotation.y;

	transform.position.x += (glfwGetKey(window, GLFW_KEY_D) - glfwGetKey(window, GLFW_KEY_A)) * moveSpeed * cosf(yaw * TORAD) +
						    (glfwGetKey(window, GLFW_KEY_S) - glfwGetKey(window, GLFW_KEY_W)) * moveSpeed * sinf(yaw * TORAD);
	transform.position.z += (glfwGetKey(window, GLFW_KEY_S) - glfwGetKey(window, GLFW_KEY_W)) * moveSpeed * cosf(yaw * TORAD) -
							(glfwGetKey(window, GLFW_KEY_D) - glfwGetKey(window, GLFW_KEY_A)) * moveSpeed * sinf(yaw * TORAD);

	transform.position.y += (glfwGetKey(window, GLFW_KEY_SPACE) - glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) * moveSpeed;

	glfwGetCursorPos(window, &mouseX, &mouseY);

	pitch += (float)(mouseY - oldY) * mouseSensitivity;
	yaw -= (float)(mouseX - oldX) * mouseSensitivity;
	clamp(pitch, -90.f, 90.f);

	oldY = (float)mouseY;
	oldX = (float)mouseX;
}

mat4 LowRenderer::Camera::getVPMatrix() const
{
	return getPerspective(false) * getViewMatrix();
}

mat4 LowRenderer::Camera::getMVPMatrix(const mat4& modelMatrix) const
{
	return getPerspective(false) * getViewMatrix() * modelMatrix;
}