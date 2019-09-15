#include <guim/target_text_input.hpp>

#include <imgui_stdlib.h>

namespace guim
{
    void target_text_input::update()
    {
        if(enabled)
        {
            background_color.push();
            foreground_color.push();

            ImGui::InputText(_label.c_str(), _target);

            background_color.pop();
            foreground_color.pop();
            
            if(sameline) { ImGui::SameLine(); }
        }
    }
}