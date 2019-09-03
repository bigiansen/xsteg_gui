#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

struct window_opengl_hints
{
    int ver_major = 3;
    int ver_minor = 0;
    int aa_samples = 1;

    constexpr window_opengl_hints() {}
};

class window
{
private:
    GLFWwindow* _wndptr;

public:
    window(
        uint32_t sz_x, 
        uint32_t sz_y, 
        const std::string& title, 
        window_opengl_hints hints = window_opengl_hints());

    bool should_close();
    GLFWwindow* wnd_ptr();
};
