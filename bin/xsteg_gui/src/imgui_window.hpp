#pragma once

#include <string>
#include <optional>
#include <imgui.h>
#include "window.hpp"

class imgui_window
{
private:
    std::string _title;
    std::optional<ImVec4> _bg_color;
    std::optional<ImVec4> _txt_color;
    bool _hidden = true;

public:
    imgui_window(const std::string& title);
    imgui_window(std::string&& title);

    void set_background_color(ImVec4 color);
    void set_text_color(ImVec4 color);

    void show();
    void hide();

    void update();

protected:
    virtual void update_proc() = 0;
};