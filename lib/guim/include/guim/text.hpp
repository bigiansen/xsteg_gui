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

        template<typename TString, typename = tt::enable_if_stringish<TString>>
        void set_text(TString&& txt)
        {
            _text = tt::forward_stringish(txt);
        }

        virtual void update() override;
    };
}