#include <guim/popup.hpp>

namespace guim
{
    popup::popup(const std::string& title_label, ImVec2 size)
        : container(size)
        , _name(title_label)
    { }

    void popup::show()
    {
        ImGui::OpenPopup(_name.c_str());
    }

    void popup::update()
    {
        if(enabled)
        {
            if(ImGui::BeginPopupModal(_name.c_str()))
            {
                container::update();
                if(ImGui::Button("Close"))
                {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }
    }
}