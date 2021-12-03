#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "utils/singleton.hpp"

#include "core/math/math.hpp"
#include "core/graph.hpp"

class Application : public Singleton<Application>
{
	friend class Singleton<Application>;

private:
	const int SCRN_HEIGHT = 720;
	const int SCRN_WIDTH = 1280;
	
	int		init();
	void	gameLoop();

	Application() {}

public:
	GLFWwindow* window = nullptr;

	Graph* graph = nullptr;

	~Application();

	void	run();
	float	getAspectRatio() const;
};