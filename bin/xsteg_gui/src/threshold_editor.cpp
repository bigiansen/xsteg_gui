#include "threshold_editor.hpp"

#include <algorithm>
#include <optional>

const static ImVec4 COLOR_RED(0.5F, 0.2F, 0.2F, 1.0F);
const static ImVec4 COLOR_GREEN(0.2F, 0.5F, 0.2F, 1.0F);
const static ImVec4 COLOR_BLUE(0.2F, 0.2F, 0.5F, 1.0F);
const static ImVec4 COLOR_GRAY(0.3F, 0.3F, 0.3F, 1.0F);

size_t threshold_editor::threshold_count()
{
    return _thresholds.size();
}

void threshold_editor::update()
{
    static std::optional<int> delete_idx;

    if(delete_idx)
    {
        auto it = _thresholds.begin() + delete_idx.value();
        _thresholds.erase(it);
        delete_idx.reset();
    }

    ImVec2 sz = ImGui::GetWindowSize();
    ImVec2 editor_sz(0, sz.y * 0.5F);
    
    ImGui::BeginChild("Threshold editor", editor_sz, true);
    {
        int idx = 0;
        for(auto it = _thresholds.begin(); it != _thresholds.end(); ++it)
        {
            auto& th = *it;
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
            ImGui::PopItemWidth();

            static const char* dir_combo_labels[2] = {
                "UP",
                "DOWN"
            };
            ImGui::PushItemWidth(56);
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

            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_FrameBg, COLOR_RED);
            ImGui::InputInt(input_r.c_str(), &th.bits.r, 0); ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_FrameBg, COLOR_GREEN);
            ImGui::InputInt(input_g.c_str(), &th.bits.g, 0); ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_FrameBg, COLOR_BLUE);
            ImGui::InputInt(input_b.c_str(), &th.bits.b, 0); ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_FrameBg, COLOR_GRAY);
            ImGui::InputInt(input_a.c_str(), &th.bits.a, 0); ImGui::SameLine();
            ImGui::PopStyleColor(4);
            ImGui::PopItemWidth();

            ImGui::Spacing();
            ImGui::SameLine();

            th.bits.r = std::min(7, std::max(th.bits.r, 0));
            th.bits.g = std::min(7, std::max(th.bits.g, 0));
            th.bits.b = std::min(7, std::max(th.bits.b, 0));
            th.bits.a = std::min(7, std::max(th.bits.a, 0));
          
            ImGui::PushItemWidth(64);
            const std::string valstr = "##value_" + std::to_string(idx);
            ImGui::InputFloat(valstr.c_str(), &th.value);
            ImGui::PopItemWidth();
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.8F, 0.25F, 0.25F, 1));
            if(ImGui::Button((" - ##" + std::to_string(idx)).c_str()))
            {
                delete_idx = idx;
            }
            ImGui::PopStyleColor();
            ImGui::Separator();

            ++idx;
        }

        if(ImGui::Button(" + "))
        {
            _thresholds.push_back(xsteg::availability_threshold());
        }
    }
    ImGui::EndChild();
}