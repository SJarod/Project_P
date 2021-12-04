#include "core/datastructure/graph.hpp"

Core::DataStructure::Graph::Graph()
{
}

Core::DataStructure::Graph::~Graph()
{
	delete scene;
}

void Core::DataStructure::Graph::loadScene(const char* filename)
{
	scene = new Scene(filename);
	getCurrentScene()->loadSceneFromFile();
}

Scene* Core::DataStructure::Graph::getCurrentScene() const
{
	return scene;
}