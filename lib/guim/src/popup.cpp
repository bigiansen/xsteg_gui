#include <guim/popup.hpp>

namespace guim
{
    void popup::show()
    {
        ImGui::OpenPopup(_label.c_str());
    }

    void popup::update()
    {
		if(!enabled) { return; }
        
		background_color.push();
		foreground_color.push();
        if(ImGui::BeginPopupModal(_label.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            container::update();
            if(ImGui::Button("Close"))
            {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
		background_color.pop();
		foreground_color.pop();
    }
}