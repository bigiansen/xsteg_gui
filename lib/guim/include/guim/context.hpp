#pragma once

#include <functional>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <guim/appwindow.hpp>
#include <guim/traits/background_color.hpp>

namespace guim
{
    class context
        : traits::background_color
    {
    private:
        appwindow* _wnd;
        ImGuiIO* _io;

    public:
        context(appwindow*);
        void start(std::function<void(void)> main_loop);
    };
}