#pragma once

#include <guim/color.hpp>
#include <guim/widget.hpp>
#include <guim/traits/background_color.hpp>
#include <guim/traits/foreground_color.hpp>

#include <imgui.h>

#include <string>
#include <functional>
#include <optional>

namespace guim
{
    typedef std::function<void()> button_click_callback_t;
    class button
        : public widget
        , public traits::background_color
		, public traits::foreground_color
    {
    protected:
        std::string _text;
        std::vector<button_click_callback_t> _callbacks;
        
        std::optional<color> _bg_color, _text_color;

    public:
        button(const std::string& text, ImVec2 size = ImVec2(0, 0));
        
        void operator+=(button_click_callback_t);
        void add_callback(button_click_callback_t);

		void set_background_color(const color&);
        void set_foreground_color(const color&);

        void update() override;
    };
}