#pragma once

#include <vector>

#include "lowrenderer/camera.hpp"
#include "interfaces/object.hpp"
#include "interfaces/renderer.hpp"
#include "resources/mesh.hpp"

#include "physics/primitives3/box.hpp"
#include "physics/primitives3/sphere.hpp"

namespace Resources
{
	class Scene
	{
	private:
		const char*				sceneName;
		Interface::RendererI&	rdr;

		std::vector<Vertex> loadMesh(const char* filename) const;
		std::vector<Vertex> loadMesh(const Primitives3::Box& b) const;
		std::vector<Vertex> loadMesh(const Primitives3::Sphere& sph) const;

		unsigned char* loadTexture(const char* filename, TextureDim& dim) const;

	public:
		std::vector<Interface::ObjectI*> staticObjs;
		std::vector<Interface::ObjectI*> dynamicObjs;

		Camera* debugCam = nullptr;
		Camera* gameCam = nullptr;
		//the used camera
		Camera* viewCam = nullptr;

		Scene(const char* sceneName, Interface::RendererI& rdr);
		~Scene();

		void startScene();
		void updateScene();

		void renderScene() const;
	};
}

using namespace Resources;