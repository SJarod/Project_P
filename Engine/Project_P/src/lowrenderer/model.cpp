#include "utils/memleaks.hpp"

#include "lowrenderer/model.hpp"

LowRenderer::Model::~Model()
{
	delete mesh;
	delete texture;
}

void LowRenderer::Model::draw() const
{
}