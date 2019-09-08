#include "application.hpp"

#include <guim/button.hpp>
#include <guim/frame.hpp>
#include <guim/window.hpp>

application::application(int w, int h, const std::string& title)
{
    guim::appwindow_opengl_hints hints;
    hints.aa_samples = 2;
    hints.ver_major = 3;
    hints.ver_minor = 3;

    _appwnd = std::make_unique<guim::appwindow>(w, h, title, hints);
    _ctx = std::make_unique<guim::context>(_appwnd.get());
}

void application::start()
{
    _ctx->start([&]()
    {
        main_loop();
    });
}

void application::main_loop()
{
    
}