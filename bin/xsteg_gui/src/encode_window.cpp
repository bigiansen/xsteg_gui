#include "encode_window.hpp"

#include <vector>
#include <xsteg/availability_map.hpp>

#include "threshold_editor.hpp"

encode_window::encode_window(window* wnd, const std::string& name)
    : imgui_window(wnd, name)
{ }

encode_window::encode_window(window* wnd, std::string&& name)
    : imgui_window(wnd, std::move(name))
{ }

void encode_window::show()
{
    imgui_window::show();
    _first_time = true;
}

void encode_window::update_proc()
{
    static std::string input_image(512, '\0');
    static std::string output_image(512, '\0');
    static std::string input_data(512, '\0');
    static bool btn_browse_input = false;
    static bool btn_browse_output = false;
    static bool btn_browse_data = false;
    static bool btn_edit_thresh = false;
    static threshold_editor th_editor;
    
    /*if(_first_time)
    {
        auto [x, y] = _wnd->get_window_size();
        float win_x = static_cast<float>(x * 0.50);
        float win_y = static_cast<float>(y * 0.60);
        ImGui::SetWindowSize(ImVec2(win_x, win_y));
    }*/
    
    // **** Input image path ****
    ImGui::InputTextWithHint("##ii", "Input image path", input_image.data(), input_image.size());
    ImGui::SameLine();
    btn_browse_input = ImGui::Button("Browse...");

    // **** Output image path ****
    ImGui::InputTextWithHint("##oi", "Output image path", output_image.data(), output_image.size());
    ImGui::SameLine();
    btn_browse_output = ImGui::Button("Browse...");

    // **** Input data file ****
    ImGui::InputTextWithHint("##df", "Input data file", input_data.data(), input_data.size());
    ImGui::SameLine();
    btn_browse_data = ImGui::Button("Browse...");

    ImGui::Separator();
    ImGui::Spacing();

    // **** Threshold editor ****
    ImGui::Text("Thresholds: (%d)", th_editor.threshold_count());

    th_editor.update();

    ImGui::Button("Generate key");
    ImGui::SameLine();
    ImGui::Button("Restore key");
    ImGui::Separator();

    ImGui::Button("Encode!");
}