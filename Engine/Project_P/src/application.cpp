#include "application.hpp"

int Application::init()
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

void Application::gameLoop()
{
    for (Object* obj : graph->getScene(0).objs)
    {
        obj->start();
    }

    graph->getScene(0).cams[(int)graph->getScene(0).mode]->start();

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

Application::~Application()
{
    delete graph;

    glfwTerminate();
}

void Application::run()
{
    if (init() < 0)
    {
        std::cout << "unable to initialize window" << std::endl;
        return;
    }

    gameLoop();
}

float Application::getAspectRatio() const
{
    return (float)SCRN_WIDTH / (float)SCRN_HEIGHT;
}