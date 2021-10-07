#include "lowrenderer/gameobject.hpp"

void LowRenderer::GameObject::draw(const mat4& VP) const
{
	model.draw(VP);
}