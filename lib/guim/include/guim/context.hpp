#pragma once

#include <functional>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <guim/appwindow.hpp>

namespace guim
{
    class context
    {
    private:
        appwindow* _wnd;
        ImVec4 _bg_color;
        ImGuiIO* _io;

    public:
        context(appwindow*);
        void set_background_color(ImVec4 color);
        void start(std::function<void(void)> main_loop);
    };
}