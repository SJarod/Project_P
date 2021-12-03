#include "resources/scene.hpp"

#include "core/api/application.hpp"

Resources::Scene::Scene()
{
	cams.push_back(new Camera);

	gos.push_back(new GameObject);
}

Resources::Scene::~Scene()
{
	for (Camera* cam : cams)
		delete cam;

	cams.clear();

	for (GameObject* go : gos)
		delete go;

	gos.clear();
}

void Resources::Scene::startScene()
{
    for (Object* obj : objs)
    {
        obj->start();
    }

    cams[(int)mode]->start();
}

void Resources::Scene::updateScene()
{
    for (Object* obj : objs)
    {
        obj->update();
    }

    cams[(int)mode]->update();
}

void Resources::Scene::displayScene() const
{
    /* Render here */
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    for (GameObject* go : gos)
    {
        go->draw(cams[(int)mode]->getVPMatrix());
    }
}