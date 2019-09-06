#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include "window.hpp"
#include "imgui_ctx.hpp"
#include "application_window.hpp"

int main(int, char**)
{
    std::remove("imgui.ini");

    window_opengl_hints hints;
    hints.ver_major = 3;
    hints.ver_minor = 3;
    hints.aa_samples = 4;
    window wnd(600, 400, "TITLE", hints);
    
    imgui_ctx ctx(&wnd);
    glfwSetWindowPos(wnd.wnd_ptr(), 2200, 300);
    application_window appwnd(&wnd);
    ctx.start([&]()
    {
        appwnd.update();
    });

    return 0;
}
