#pragma once

#include <guim/traits/background_color.hpp>
#include <guim/traits/foreground_color.hpp>
#include <guim/labeled_widget.hpp>
#include <guim/type_traits.hpp>
#include <string>

namespace guim
{
    class target_text_input : public labeled_widget
    {
    protected:
        std::string _label;
        std::string* _target;
        size_t _max_len = 0;

    public:
		traits::background_color background_color;
		traits::foreground_color foreground_color;

        template<typename TStr, typename = tt::enable_if_stringish<TStr>>
        target_text_input(
            TStr&& label, 
            std::string* target,
            size_t max_len, 
            ImVec2 size = ImVec2(0, 0))
            : labeled_widget(std::forward<TStr>(label), size)
            , _target(target)
            , _max_len(max_len)
        { }

        void update() override;
    };
}