#include <guim/traits/foreground_color.hpp>

namespace guim::traits
{
    void foreground_color::set_foreground_color(const color& col) noexcept
    {
        _fg_color = col;
    }

    void foreground_color::reset_foreground_color() noexcept
    {
        _fg_color.reset();
    }

    color foreground_color::get_foreground_color() const noexcept
    {
        return *_fg_color;
    }

    void foreground_color::push_foreground_color()
    {
        if(_fg_color)
        {
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Text, *_fg_color);
        }
    }

    void foreground_color::pop_foreground_color()
    {
        ImGui::PopStyleColor(1);
    }
}