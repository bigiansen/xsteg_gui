#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stdio.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include <guim/window.hpp>
#include <guim/context.hpp>

#include "application.hpp"

int main(int, char**)
{
    std::remove("imgui.ini");

    application app(800, 600, "xsteg GUI");
    app.start();

    return 0;
}
