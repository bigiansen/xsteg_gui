#pragma once

#include <guim/popup.hpp>
#include <guim/text.hpp>
#include <guim/type_traits.hpp>
#include <string>

namespace guim
{
    class msg_popup : public popup
    {
    protected:
        guim::text* _text;
        bool _selectable = false;

    public:
        template<typename TStr0, typename TStr1, 
            typename = tt::enable_if_stringish<TStr0, TStr1>>
        msg_popup(
            TStr0&& label,
            TStr1&& msg,
            bool selectable = false,
            ImVec2 size = ImVec2(0, 0))
            : popup(tt::forward_stringish(label), size)
        {
            _text = add_widget<guim::text>(tt::forward_stringish(msg));
        }

        template<typename TString, typename = tt::enable_if_string<TString>>
        void set_text(TString&& txt)
        {
            _text->set_text(tt::forward_stringish(txt));
        }
    };
}