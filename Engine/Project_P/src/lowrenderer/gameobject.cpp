#include "lowrenderer/gameobject.hpp"

void LowRenderer::GameObject::start()
{
	Object::start();
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