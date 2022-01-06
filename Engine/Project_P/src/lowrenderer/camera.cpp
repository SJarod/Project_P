#include "lowrenderer/camera.hpp"

#include "core/engine/application.hpp"

#include <iostream>

LowRenderer::Camera::Camera()
{
	aspect = Application::getInstance()->getAspectRatio();
}

mat4 LowRenderer::Camera::getViewMatrix() const
{
	return rotateXMatrix(transform.rotation.x) * rotateYMatrix(-transform.rotation.y) * translateMatrix(-transform.position);
}

mat4 LowRenderer::Camera::getProjMatrix(const bool ortho) const
{
	if (ortho)
		return orthographic(-orthographicRange, orthographicRange, -orthographicRange, orthographicRange, near, far);

	return perspective(fovY, aspect, near, far);
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
	return getProjMatrix(isOrthographic) * getViewMatrix();
}

mat4 LowRenderer::Camera::getMVPMatrix(const mat4& modelMatrix) const
{
	return getProjMatrix(isOrthographic) * getViewMatrix() * modelMatrix;
}