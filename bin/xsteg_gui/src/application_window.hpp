#pragma once

#include "window.hpp"

enum class application_window_nav
{
    MAIN_MENU
};

class application_window
{
private:
    window* _wnd;
    application_window_nav _nav;

public:
    application_window(window*);
    void update();
};