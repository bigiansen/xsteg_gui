#pragma once

#include <guim/color.hpp>
#include <guim/labeled_widget.hpp>
#include <guim/traits/background_color.hpp>
#include <guim/traits/foreground_color.hpp>

#include <imgui.h>

#include <string>
#include <functional>
#include <optional>
#include <vector>

namespace guim
{
    typedef std::function<void()> button_click_callback_t;

    class button : public labeled_widget
    {
    protected:
        std::vector<button_click_callback_t> _callbacks;		

    public:
		traits::background_color background_color;
		traits::foreground_color foreground_color;

        template<typename TString, typename = tt::enable_if_stringish<TString>>
        button(TString&& text, ImVec2 size = ImVec2(0, 0))
            : labeled_widget(text, size)
        { }
        
        void operator+=(button_click_callback_t);
        void add_callback(button_click_callback_t);

        void update() override;
    };
}