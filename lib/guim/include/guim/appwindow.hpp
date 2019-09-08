#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <utility>

namespace guim
{
    struct appwindow_opengl_hints
    {
        int ver_major = 3;
        int ver_minor = 3;
        int aa_samples = 1;

        constexpr appwindow_opengl_hints() {}
    };

    class appwindow
    {
    private:
        GLFWwindow* _wndptr;

    public:
        appwindow(
            uint32_t sz_x, 
            uint32_t sz_y, 
            const std::string& title, 
            appwindow_opengl_hints hints = appwindow_opengl_hints());

        bool should_close();
        GLFWwindow* wnd_ptr();

        std::pair<int, int> get_window_size();
    };
}