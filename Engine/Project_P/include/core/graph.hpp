#pragma once

#include <vector>

#include "resources/scene.hpp"

namespace Core
{
	namespace DataStructure
	{
		class Graph
		{
		private:
			std::vector<Scene*> scns;

		public:
			Graph();
			~Graph();

			Scene& getScene(const unsigned int index) const;
		};
	}
}

using namespace Core::DataStructure;