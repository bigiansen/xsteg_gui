#pragma once

#include <string>
#include <optional>
#include <map>
#include <memory>

#include <imgui.h>
#include "window.hpp"

class imgui_window
{
protected:
    window* _wnd = nullptr;
    std::string _title;
    std::optional<ImVec4> _bg_color;
    std::optional<ImVec4> _txt_color;
    bool _show = false;
    std::map<std::string, std::unique_ptr<imgui_window>> _children;

public:
    imgui_window(window*, const std::string& title);
    imgui_window(window*, std::string&& title);

    template<typename TWindow>
    TWindow* add_child_window(const std::string& name)
    {
        static_assert(std::is_base_of_v<imgui_window, std::decay_t<TWindow>>);
        auto [iter, ok] = _children.emplace(name, std::make_unique<TWindow>(_wnd, name));
        return iter->second.get();
    }

    void set_background_color(ImVec4 color);
    void set_text_color(ImVec4 color);

    virtual void show();
    virtual void hide();

    void update();

protected:
    virtual void update_proc() = 0;
};