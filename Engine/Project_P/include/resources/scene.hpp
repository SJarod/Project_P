#pragma once

#include <vector>

#include "lowrenderer/camera.hpp"
#include "lowrenderer/gameobject.hpp"

namespace Resources
{
	enum class SceneMode
	{
		DEBUG = 0,
		GAME = 1,
	};

	class Scene
	{
	private:

	public:
		std::vector<Camera*>		cams;
		std::vector<GameObject*>	gos;

		SceneMode					mode = SceneMode::DEBUG;

		Scene();
		~Scene();

		void updateScene(GLFWwindow* window);
		void displayScene() const;
	};
}

using namespace Resources;