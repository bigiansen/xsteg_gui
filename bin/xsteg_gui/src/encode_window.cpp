#include "encode_window.hpp"

encode_window::encode_window(window* wnd, const std::string& name)
    : imgui_window(wnd, name)
{ }

encode_window::encode_window(window* wnd, std::string&& name)
    : imgui_window(wnd, std::move(name))
{ }

void encode_window::update_proc()
{
    static bool window_open = true;
    static std::string input_image(512, '\0');
    static bool btn_browse = false;
    static bool btn_edit_thresh = false;
    
    auto [x, y] = _wnd->get_window_size();
    float win_x = static_cast<float>(x * 0.50);
    float win_y = static_cast<float>(y * 0.60);
    ImGui::SetWindowSize(ImVec2(win_x, win_y));
    ImGui::InputTextWithHint(
        "", 
        "Input image path", 
        input_image.data(), 
        input_image.size()
    );
    ImGui::SameLine();
    btn_browse = ImGui::Button("Browse");
    btn_edit_thresh = ImGui::Button("Edit thresholds");
}