#include "core/engine/application.hpp"

int main()
{
    Application* app = Application::getInstance();
    app->run();

    app->end();

    return 0;
}