#include "lowrenderer/gameobject.hpp"

#include "core/engine/application.hpp"

void LowRenderer::GameObject::start()
{
	Object::start();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	model.setRenderCam(Application::getInstance()->graph->getCurrentScene()->viewCam);
}

void LowRenderer::GameObject::update()
{
	Object::update();
}

void LowRenderer::GameObject::render()
{
	Object::render();

	model.draw();
}