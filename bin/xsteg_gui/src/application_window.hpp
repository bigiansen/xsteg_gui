#pragma once

#include "window.hpp"

class application_window
{
private:
    window* _wnd;

public:
    application_window(window*);
    void update();
};