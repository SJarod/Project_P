#include "core/api/application.hpp"

#include <iostream>

int Core::API::Application::init()
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCRN_WIDTH, SCRN_HEIGHT, "Project_P", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //initializing leak check
    initMemleaksDebug();

    //initializing graph
    graph = new Graph;

    return 0;
}

void Core::API::Application::gameLoop()
{
    graph->getScene(0).startScene();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        graph->getScene(0).updateScene();
        graph->getScene(0).displayScene();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

Core::API::Application::~Application()
{
    delete graph;

    glfwTerminate();
}

void Core::API::Application::run()
{
    if (init() < 0)
    {
        std::cout << "unable to initialize window" << std::endl;
        return;
    }

    gameLoop();
}

float Core::API::Application::getAspectRatio() const
{
    return (float)SCRN_WIDTH / (float)SCRN_HEIGHT;
}