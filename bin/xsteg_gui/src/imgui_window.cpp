#include "imgui_window.hpp"

imgui_window::imgui_window(window* wnd, const std::string& title)
{
    _title = title;
    _wnd = wnd;
}

imgui_window::imgui_window(window* wnd, std::string&& title)
{
    _title = std::move(title);
    _wnd = wnd;
}

void imgui_window::set_background_color(ImVec4 color)
{
    _bg_color = color;
}

void imgui_window::set_text_color(ImVec4 color)
{
    _txt_color = color;
}

void imgui_window::show() { _show = true; }

void imgui_window::hide() { _show = false; }

void imgui_window::update()
{
    if(_show)
    {
        int pop_count = 0;
        if(_bg_color)
        { 
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_WindowBg, _bg_color.value());
            ++pop_count;
        }

        if(_txt_color)
        { 
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Text, _txt_color.value()); 
            ++pop_count;
        }

        ImGui::Begin(_title.c_str(), &_show);
        update_proc();
        ImGui::End();
        
        ImGui::PopStyleColor(pop_count);
    }
}