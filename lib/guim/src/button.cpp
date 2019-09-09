#include <guim/button.hpp>

namespace guim
{
    button::button(const std::string& text, ImVec2 size)
        : _text(text)
        , widget(size)
    { }

    void button::operator+=(button_click_callback_t cback)
    {
        _callbacks.push_back(cback);
    }

    void button::add_callback(button_click_callback_t cback)
    {
        *this += cback;
    }

    void button::update()
    {
        if(enabled)
        {
            background_color::push();
            foreground_color::push();
            if(ImGui::Button(_text.c_str(), _size)) 
            { 
                for (auto& cback : _callbacks)
                {
                    cback();
                }
            }
            foreground_color::pop();
            background_color::pop();

            if(sameline)
            {
                ImGui::SameLine();
            }
        }
    }
}