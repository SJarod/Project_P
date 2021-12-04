#include "lowrenderer/model.hpp"

#include "utils/memleaks.hpp"

LowRenderer::Model::Model()
{
	shader = new Shader("base");
	mesh = new Mesh;
	mesh->loadMesh("the_noble_craftsman.obj");
	mesh->transform.scale = { 10.f, 10.f, 10.f };
}

LowRenderer::Model::~Model()
{
	delete shader;
	delete mesh;
}

void LowRenderer::Model::draw() const
{
	if (!renderCam)
		return;

	mat4 VP = renderCam->getVPMatrix();

	//rendering
	shader->use();
	shader->passMat4(VP * mesh->transform.getModelMatrix(), "mvp");

	mesh->render();
}