#pragma once

#include <guim/appwindow.hpp>
#include <guim/context.hpp>
#include <memory>

class application
{
private:
    std::unique_ptr<guim::appwindow> _appwnd;
    std::unique_ptr<guim::context> _ctx;

public:
    application(int w, int h, const std::string& title);
    void start();
};