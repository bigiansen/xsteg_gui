#pragma once

#include <guim/type_traits.hpp>
#include <guim/widget.hpp>
#include <guim/traits/background_color.hpp>
#include <guim/traits/foreground_color.hpp>
#include <functional>
#include <string>
#include <vector>

namespace guim
{
    class selectable : public widget
    {
    protected:
        std::string _label;
        std::vector<std::function<void()>> _callbacks;

    public:
		traits::background_color background_color;
		traits::foreground_color foreground_color;

        template<typename TStr, typename = tt::enable_if_stringish<TStr>>
        selectable(TStr&& label)
            : _label(label)
        { }

        virtual void update() override;

        void operator+=(std::function<void()> cback);
        void add_callback(std::function<void()> cback);
    };
}