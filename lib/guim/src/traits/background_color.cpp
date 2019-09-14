#include <guim/traits/background_color.hpp>

namespace guim::traits
{
    void background_color::push()
    {
        if(color_background)
        {
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ChildBg, *color_background);
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_FrameBg, *color_background);
        }
    }

    void background_color::pop()
    {
        if(color_background)
        {
            ImGui::PopStyleColor(2);
        }
    }
}