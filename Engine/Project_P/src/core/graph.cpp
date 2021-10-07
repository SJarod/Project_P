#include "core/graph.hpp"

Core::DataStructure::Graph::Graph()
{
	scns.push_back(new Scene);
}

Core::DataStructure::Graph::~Graph()
{
	for (Scene* scn : scns)
		delete scn;

	scns.clear();
}

Scene& Core::DataStructure::Graph::getScene(const unsigned int index) const
{
	return *scns[index];
}