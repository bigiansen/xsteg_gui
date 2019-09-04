#pragma once

#include "window.hpp"
#include "imgui_window.hpp"

class application_window
{
private:
    window* _wnd;

public:
    application_window(window*);
    void update();

    window* get_window() { return _wnd; }
    GLFWwindow* wnd_ptr() { return _wnd->wnd_ptr(); }    
};