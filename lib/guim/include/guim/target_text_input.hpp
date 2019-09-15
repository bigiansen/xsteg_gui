#pragma once

#include <guim/traits/background_color.hpp>
#include <guim/traits/foreground_color.hpp>
#include <guim/type_traits.hpp>
#include <guim/widget.hpp>
#include <string>

namespace guim
{
    class target_text_input : public widget
    {
    protected:
        std::string _label;
        std::string* _target;
        size_t _max_len = 0;

    public:
		traits::background_color background_color;
		traits::foreground_color foreground_color;

        template<typename TString, typename = tt::enable_if_string<TString>>
        target_text_input(
            TString&& label, 
            std::string* target,
            size_t max_len, 
            ImVec2 size = ImVec2(0, 0))
            : _label(std::forward(label))
            , _target(target)
            , _max_len(max_len)
        { }

        void update() override;
    };
}