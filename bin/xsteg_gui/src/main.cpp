#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include <guim/window.hpp>
#include <guim/context.hpp>

int main(int, char**)
{
    std::remove("imgui.ini");

    guim::appwindow_opengl_hints hints;
    hints.ver_major = 3;
    hints.ver_minor = 3;
    hints.aa_samples = 4;
    guim::appwindow wnd(800, 600, "TITLE", hints);
    
    guim::context ctx(&wnd);
    glfwSetWindowPos(wnd.wnd_ptr(), 400, 300);
    ctx.start([&]()
    {
        // ...
    });

    return 0;
}
