#include "utils/memleaks.hpp"

#include "resources/scene.hpp"

Resources::Scene::Scene(const char* sn)
    : sceneName(sn)
{
    debugCam = new Camera;
    viewCam = debugCam;
    dynamicObjs.push_back(debugCam);

    staticObjs.push_back(new GameObject);
}

Resources::Scene::~Scene()
{
    for (Object* obj : staticObjs)
        delete obj;

    for (Object* obj : dynamicObjs)
        delete obj;

    staticObjs.clear();
    dynamicObjs.clear();
}

void Resources::Scene::startScene()
{
    for (Object* obj : staticObjs)
    {
        obj->start();
    }

    for (Object* obj : dynamicObjs)
    {
        obj->start();
    }
}

void Resources::Scene::updateScene()
{
    for (Object* obj : dynamicObjs)
    {
        obj->update();
    }
}

void Resources::Scene::renderScene() const
{
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (Object* obj : staticObjs)
    {
        obj->render();
    }

    for (Object* obj : dynamicObjs)
    {
        obj->render();
    }

    glDisable(GL_DEPTH_TEST);
}