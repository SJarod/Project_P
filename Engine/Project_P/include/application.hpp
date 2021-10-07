#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "core/math/math.hpp"
#include "core/graph.hpp"

class Application
{
private:
	const int SCRN_HEIGHT = 720;
	const int SCRN_WIDTH = 1280;

	GLFWwindow* window = nullptr;

	Graph* graph = nullptr;
	
	int		init();
	void	gameLoop();

public:
	~Application();

	void	run();
	float	getAspectRatio() const;
};