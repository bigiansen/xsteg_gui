#pragma once

#include <guim/type_traits.hpp>
#include <guim/widget.hpp>
#include <guim/traits/foreground_color.hpp>
#include <string>

namespace guim
{
    class text : public widget
    {
    protected:
        std::string _text;

    public:
		traits::foreground_color foreground_color;

        text(const std::string& text, ImVec2 size = ImVec2(0, 0));

        template<typename TStr, typename = tt::enable_if_stringish<TStr>>
        void set_text(TStr&& txt)
        {
            _text = std::forward<TStr>(txt);
        }

        virtual void update() override;
    };
}