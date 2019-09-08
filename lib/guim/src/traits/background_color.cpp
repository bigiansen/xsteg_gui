#include <guim/traits/background_color.hpp>

namespace guim::traits
{
    void background_color::set_background_color(const color& col) noexcept
    {
        _bg_color = col;
    }

    void background_color::reset_background_color() noexcept
    {
        _bg_color.reset();
    }

    color background_color::get_background_color() const noexcept
    {
        return *_bg_color;
    }

    void background_color::push_background_color()
    {
        if(_bg_color)
        {
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ChildBg, *_bg_color);
        }
    }

    void background_color::pop_background_color()
    {
        ImGui::PopStyleColor(1);
    }
}