#include "imgui_window.hpp"

imgui_window::imgui_window(const std::string& title)
{
    _title = title;
}

imgui_window::imgui_window(std::string&& title)
{
    _title = std::move(title);
}

void imgui_window::set_background_color(ImVec4 color)
{
    _bg_color = color;
}

void imgui_window::set_text_color(ImVec4 color)
{
    _txt_color = color;
}

void imgui_window::show() { _hidden = false; }

void imgui_window::hide() { _hidden = true; }

void imgui_window::update()
{
    if(!_hidden)
    {
        if(_bg_color) 
            { ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_WindowBg, _bg_color.value()); }

        if(_txt_color)
            { ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Text, _txt_color.value()); }

        ImGui::Begin(_title.c_str(), NULL);
        update_proc();
        ImGui::End();
        
        ImGui::PopStyleColor(2);
    }
}