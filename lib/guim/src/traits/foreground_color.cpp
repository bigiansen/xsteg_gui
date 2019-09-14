#include <guim/traits/foreground_color.hpp>

namespace guim::traits
{
    void foreground_color::push()
    {
        if(color_foreground)
        {
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Text, *color_foreground);            
        }
    }

    void foreground_color::pop()
    {
        if(color_foreground)
        {
            ImGui::PopStyleColor(1);
        }
    }
}