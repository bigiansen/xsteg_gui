#include "application_window.hpp"

#include <iostream>
#include <imgui.h>
#include "encode_window.hpp"

application_window::application_window(window* wnd)
{
    _wnd = wnd;
}

void application_window::update()
{
    static encode_window encode_window(_wnd, "Encode");

    auto [x, y] = _wnd->get_window_size();
    ImGui::SetNextWindowSize(ImVec2((float)x, (float)y));

    auto flags = 
          ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground
        | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration
        | ImGuiWindowFlags_::ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_::ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_::ImGuiWindowFlags_NoBringToFrontOnFocus;
    
    static bool encode_selected = false;
    static bool decode_selected = false;
    static bool genmaps_selected = false;
    ImGui::Begin("ApplicationWindow", NULL, flags);
    {
        static const int ITEM_COUNT = 3;

        ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::SetWindowPos(ImVec2(0, 0));
        encode_selected = ImGui::Button("Encode", ImVec2((x / ITEM_COUNT)*0.95F, 0)); 
        ImGui::SameLine();
        decode_selected = ImGui::Button("Decode", ImVec2((x / ITEM_COUNT)*0.95F, 0)); 
        ImGui::SameLine();
        genmaps_selected = ImGui::Button("Generate maps", ImVec2((x / ITEM_COUNT)*0.985F, 0)); 
        ImGui::PopStyleVar(1);

        if(encode_selected)
        {
            encode_window.show();
        }

        encode_window.update();
    }
    ImGui::End();
}