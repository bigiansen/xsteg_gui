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
        if(_enabled)
        {
            int pop_count = 0;
            if(_bg_color)
            {
                ImGui::PushStyleColor(ImGuiCol_Button, *_bg_color);
                ++pop_count;
            }
            if(_text_color)
            {
                ImGui::PushStyleColor(ImGuiCol_Text, *_text_color);
                ++pop_count;
            }

            if(ImGui::Button(_text.c_str(), _size)) 
            { 
                for (auto& cback : _callbacks)
                {
                    cback();
                }
            }

            ImGui::PopStyleColor(pop_count);
        }
    }

    void button::set_background_color(const color& col)
    {
        _bg_color = col;
    }

    void button::set_foreground_color(const color& col)
    {
        _text_color = col;
    }
}