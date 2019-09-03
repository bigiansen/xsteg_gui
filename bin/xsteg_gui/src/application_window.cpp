#include "application_window.hpp"

#include <imgui.h>
#include "encode_window.hpp"

application_window::application_window(window* wnd)
{
    _wnd = wnd;
}

void application_window::update()
{
    auto flags = 
        ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | 
        ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground;

    static encode_window encode_window(_wnd, "Encode");
    static bool encode_selected = false;
    static bool decode_selected = false;

    ImGui::BeginMainMenuBar();
    {
        ImGui::MenuItem("Encode", "E", &encode_selected);
        ImGui::MenuItem("Decode", "D", &decode_selected);
        ImGui::MenuItem("Gen Maps", "G", &encode_selected);
    }
    ImGui::EndMainMenuBar();

    if(encode_selected) 
    { 
        encode_window.update(); 
    }
}