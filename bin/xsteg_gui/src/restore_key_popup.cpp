#include "restore_key_popup.hpp"

#include <guim/msg_popup.hpp>

void restore_key_popup::init_widgets()
{
    _input = add_widget<guim::text_input>("##restore_key_input", 4096, ImVec2(-1, 0));
}

void restore_key_popup::show()
{
    ImGui::OpenPopup(_label.c_str());
}

void restore_key_popup::update()
{
    if(!enabled) { return; }
    static guim::msg_popup* invalid_format_popup = 
        add_widget<guim::msg_popup>("Error", "Invalid key format!");

    background_color.push();
    foreground_color.push();
    if(ImGui::BeginPopupModal(_label.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        container::update();
        if(ImGui::Button("Cancel"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if(ImGui::Button("Restore"))
        {
            try
            {
                _thresholds = xsteg::parse_thresholds_key(_input->text());
                ImGui::CloseCurrentPopup();
            }
            catch(const std::exception&)
            {
                invalid_format_popup->show();
            }
        }
        ImGui::EndPopup();
    }
    background_color.pop();
    foreground_color.pop();

    if(sameline) { ImGui::SameLine(); }
}