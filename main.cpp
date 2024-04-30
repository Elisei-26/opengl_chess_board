#include <stdio.h>
#include <cassert>
#include "glfw_application.hpp"

using namespace opengles_workspace;

int main()
{
    GlfwApplication app(1000, 1000);
    return app.run();
}