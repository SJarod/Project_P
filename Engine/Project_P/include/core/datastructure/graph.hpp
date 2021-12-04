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
			Scene* scene = nullptr;

		public:
			Graph();
			~Graph();

			void loadScene(const char* filename);

			Scene* getCurrentScene() const;
		};
	}
}

using namespace Core::DataStructure;