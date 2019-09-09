#pragma once

#include <guim/appwindow.hpp>
#include <guim/window.hpp>

class main_window final : guim::window
{
private:
    guim::appwindow* _appwnd;
public:
    main_window(guim::appwindow* appwnd);
    void update() override;
};