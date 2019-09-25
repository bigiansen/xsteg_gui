#pragma once

#include <guim/container.hpp>
#include <guim/type_traits.hpp>
#include <guim/traits/background_color.hpp>
#include <guim/traits/foreground_color.hpp>
#include <string>

namespace guim
{
    class popup : public container
    {
    protected:
        std::string _label;

    public:
		traits::background_color background_color;
		traits::foreground_color foreground_color;

        template<typename TStr, typename = tt::enable_if_stringish<TStr>>
        popup(TStr&& label, ImVec2 size = ImVec2(0, 0))
            : _label(label)
        { }

        virtual void show();
        virtual void update() override;
    };
}