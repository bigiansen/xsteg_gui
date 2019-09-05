#pragma once

#include <string>
#include <optional>
#include <map>
#include <memory>
#include <vector>

#include <imgui.h>
#include "window.hpp"

class application_window;
class imgui_window
{
protected:
    application_window* _appwnd = nullptr;
    std::string _title;
    std::optional<ImVec4> _bg_color;
    std::optional<ImVec4> _txt_color;
    bool _show = false;
    std::map<std::string, std::unique_ptr<imgui_window>> _children;

public:
    imgui_window(application_window*, const std::string& title);
    imgui_window(application_window*, std::string&& title);

    template<typename TWin, typename... TArgs>
    TWin* add_child_window(const std::string& name, TArgs... args)
    {
        static_assert(std::is_base_of_v<imgui_window, std::decay_t<TWin>>);
        auto [it, ok] = _children.emplace(name, std::make_unique<TWin>(args...));
        return dynamic_cast<TWin*>(it->second.get());
    }

    void set_background_color(ImVec4 color);
    void set_text_color(ImVec4 color);

    virtual void show();
    virtual void hide();

    void update();

protected:
    virtual void update_proc() = 0;
};