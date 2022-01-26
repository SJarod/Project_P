#include "core/engine/application.hpp"

#include "lowrenderer/gameobject.hpp"

void LowRenderer::GameObject::start()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	model.setRenderCam(Application::getInstance()->graph->getCurrentScene()->viewCam);
}

void LowRenderer::GameObject::update()
{
}

void LowRenderer::GameObject::render()
{
	model.draw();
}