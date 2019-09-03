#pragma once

#include <functional>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.hpp"

class imgui_ctx
{
private:
    window* _wnd;
    ImVec4 _bg_color;
    ImGuiIO* _io;

public:
    imgui_ctx(window*);
    void set_background_color(ImVec4 color);
    void start(std::function<void(void)> main_loop);
};