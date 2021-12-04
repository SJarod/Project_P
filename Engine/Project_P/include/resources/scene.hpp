#pragma once

#include <vector>

#include "lowrenderer/camera.hpp"
#include "lowrenderer/gameobject.hpp"
#include "lowrenderer/object.hpp"

namespace Resources
{
	class Scene
	{
	private:
		const char* sceneName;

	public:
		std::vector<Object*> objs;

		Camera* debugCam = nullptr;
		Camera* gameCam = nullptr;
		//the used camera
		Camera* viewCam = nullptr;

		Scene() = default;
		Scene(const char* sceneName);
		~Scene();

		void loadSceneFromFile();

		void startScene();
		void updateScene();

		void renderScene() const;
	};
}

using namespace Resources;