#include "application_window.hpp"

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
        | ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar;
    
    bool encode_selected = false;
    bool decode_selected = false;
    bool genmaps_selected = false;
    ImGui::Begin("ApplicationWindow", NULL, flags);
    {
        static const int ITEM_COUNT = 3;

        ImGui::SetWindowPos(ImVec2(0, 0));
        encode_selected = ImGui::Button("Encode", ImVec2((x / ITEM_COUNT)*0.95F, 0)); 
        ImGui::SameLine();
        decode_selected = ImGui::Button("Decode", ImVec2((x / ITEM_COUNT)*0.95F, 0)); 
        ImGui::SameLine();
        genmaps_selected = ImGui::Button("Generate maps", ImVec2((x / ITEM_COUNT)*0.985F, 0)); 
    }
    ImGui::End();

    if(encode_selected)
    {
        encode_window.show();
    }

    encode_window.update();
}