#pragma once

#include <guim/popup.hpp>
#include <guim/text.hpp>
#include <guim/text_input.hpp>
#include <guim/type_traits.hpp>
#include <string>
#include <variant>

namespace guim
{
    class msg_popup : public popup
    {
    protected:
        guim::text* _textw = nullptr;
        guim::text_input* _textinputw = nullptr;
        bool _selectable = false;

    public:
        template<typename TStr0, typename TStr1, 
            typename = tt::enable_if_stringish<TStr0, TStr1>>
        msg_popup(
            TStr0&& label,
            TStr1&& msg,
            bool selectable = false,
            ImVec2 size = ImVec2(0, 0))
            : popup(std::forward<TStr0>(label), size)
            , _selectable(selectable)
        {
            if(!selectable)
            {
                _textw = add_widget<guim::text>(std::forward<TStr1>(msg));
            }
            else
            {
                _textinputw = add_widget<guim::text_input>("##msgpopup_txt_input");
                _textinputw->set_text(std::forward<TStr1>(msg));
                _textinputw->readonly = true;
            }
        }

        template<typename TStr, typename = tt::enable_if_stringish<TStr>>
        void set_text(TStr&& txt)
        {
            if(_selectable)
            {
                _textinputw->set_text(std::forward<TStr>(txt));
            }
            else
            {
                _textw->set_text(std::forward<TStr>(txt));
            }
        }

        void show() override
        {
            popup::show();
        }

        template<typename TStr, typename = tt::enable_if_stringish<TStr>>
        void show(TStr&& text)
        {
            set_text(std::forward<TStr>(text));
            popup::show();
        }

        template<typename TStr0, typename TStr1, 
            typename = tt::enable_if_stringish<TStr0, TStr1>>
        void show(TStr0&& title, TStr1&& text)
        {
            set_text(std::forward<TStr0>(text));
            _name = std::forward<TStr1>(title);
            popup::show();
        }
    };
}