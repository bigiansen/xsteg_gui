#include "encode_window.hpp"

#include <vector>
#include <xsteg/availability_map.hpp>

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
    static std::vector<xsteg::availability_threshold> thresholds;

    static std::string input_image(512, '\0');
    static std::string output_image(512, '\0');
    static std::string input_data(512, '\0');
    static bool btn_browse_input = false;
    static bool btn_browse_output = false;
    static bool btn_browse_data = false;
    static bool btn_edit_thresh = false;
    
    auto [x, y] = _wnd->get_window_size();
    float win_x = static_cast<float>(x * 0.50);
    float win_y = static_cast<float>(y * 0.60);
    ImGui::SetWindowSize(ImVec2(win_x, win_y));
    
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
    ImGui::Text("Thresholds: (%d)", thresholds.size());

    ImVec2 sz = ImGui::GetWindowSize();
    ImVec2 editor_sz(0, sz.y * 0.5F);
    ImGui::BeginChild("Threshold editor", editor_sz, true, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
    {
        int idx = 0;
        for(auto& th : thresholds)
        {
            static const char* datatype_combo_labels[9] = {
                "VALUE_RED",    "VALUE_GREEN",  "VALUE_BLUE", 
                "SATURATION",   "LUMINANCE",    "SATURATION",
                "ALPHA",        "AVERAGE_RGBA", "AVERAGE_RGB"
            };

            ImGui::Text("[%d]:", idx);
            ImGui::PushItemWidth(128);
            const std::string typestr = "##type_" + std::to_string(idx);
            ImGui::Combo(typestr.c_str(), (int*)&th.data_type, datatype_combo_labels, 9);
            ImGui::SameLine();

            static const char* dir_combo_labels[2] = {
                "UP",
                "DOWN"
            };

            const std::string dirstr = "##dir_" + std::to_string(idx);
            ImGui::Combo(dirstr.c_str(), (int*)&th.direction, dir_combo_labels, 2);
            ImGui::PopItemWidth();
            ImGui::SameLine();

            const std::string input_r = "##r_" + std::to_string(idx);
            const std::string input_g = "##g_" + std::to_string(idx);
            const std::string input_b = "##b_" + std::to_string(idx);
            const std::string input_a = "##a_" + std::to_string(idx);

            ImGui::Spacing();
            ImGui::SameLine();

            ImGui::PushItemWidth(16);
            ImGui::Text("R"); ImGui::SameLine();
            ImGui::InputInt(input_r.c_str(), &th.bits.r, 0); ImGui::SameLine();
            ImGui::Text("G"); ImGui::SameLine();
            ImGui::InputInt(input_g.c_str(), &th.bits.g, 0); ImGui::SameLine();
            ImGui::Text("B"); ImGui::SameLine();
            ImGui::InputInt(input_b.c_str(), &th.bits.b, 0); ImGui::SameLine();
            ImGui::Text("A"); ImGui::SameLine();
            ImGui::InputInt(input_a.c_str(), &th.bits.a, 0); ImGui::SameLine();
            ImGui::PopItemWidth();

            ImGui::Spacing();
            ImGui::SameLine();

            th.bits.r = std::min(7, std::max(th.bits.r, 0));
            th.bits.g = std::min(7, std::max(th.bits.g, 0));
            th.bits.b = std::min(7, std::max(th.bits.b, 0));
            th.bits.a = std::min(7, std::max(th.bits.a, 0));
          
            const std::string valstr = "##value_" + std::to_string(idx);
            ImGui::InputFloat(valstr.c_str(), &th.value);
            ImGui::Separator();

            ++idx;
        }

        if(ImGui::Button(" + "))
        {
            thresholds.push_back(xsteg::availability_threshold());
        }
    }
    ImGui::EndChild();

    ImGui::Button("Generate key");
    ImGui::SameLine();
    ImGui::Button("Restore key");
    ImGui::Separator();

    ImGui::Button("Encode!");
}