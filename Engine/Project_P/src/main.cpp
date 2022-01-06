#include "core/engine/application.hpp"

int main()
{
    Application* app = Application::getInstance();
    app->run();

    app->destroy();

    return 0;
}