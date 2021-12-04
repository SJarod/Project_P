#include "resources/scene.hpp"

#include "utils/memleaks.hpp"

Resources::Scene::Scene(const char* sn)
    : sceneName(sn)
{
}

Resources::Scene::~Scene()
{
    for (Object* obj : objs)
        delete obj;

    objs.clear();
}

void Resources::Scene::loadSceneFromFile()
{
    debugCam = new Camera;
    viewCam = debugCam;
    objs.push_back(debugCam);

    objs.push_back(new GameObject);
}

void Resources::Scene::startScene()
{
    for (Object* obj : objs)
    {
        obj->start();
    }
}

void Resources::Scene::updateScene()
{
    for (Object* obj : objs)
    {
        obj->update();
    }
}

void Resources::Scene::renderScene() const
{
    /* Render here */
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    for (Object* obj : objs)
    {
        obj->render();
    }
}