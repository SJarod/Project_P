#include "lowrenderer/model.hpp"

LowRenderer::Model::Model()
{
	shader = new Shader("base");
	mesh = new Mesh;
}

LowRenderer::Model::~Model()
{
	delete shader;
	delete mesh;
}

void LowRenderer::Model::draw(const mat4& VP) const
{
	//rendering
	shader->use();
	shader->passMat4(VP * mesh->transform.getModelMatrix(), "mvp");

	mesh->render();
}