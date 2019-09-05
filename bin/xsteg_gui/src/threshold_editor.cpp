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
            ImGui::SameLine();
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

            std::string sr = (th.bits.r <= -1)
                ? "-" : std::to_string(std::clamp(th.bits.r, 0, 7));
            std::string sg = (th.bits.g <= -1)
                ? "-" : std::to_string(std::clamp(th.bits.g, 0, 7));
            std::string sb = (th.bits.b <= -1)
                ? "-" : std::to_string(std::clamp(th.bits.b, 0, 7));
            std::string sa = (th.bits.a <= -1)
                ? "-" : std::to_string(std::clamp(th.bits.a, 0, 7));

            
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_FrameBg, COLOR_RED);
            ImGui::InputText(input_r.c_str(), sr.data(), 2); ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_FrameBg, COLOR_GREEN);
            ImGui::InputText(input_g.c_str(), sg.data(), 2); ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_FrameBg, COLOR_BLUE);
            ImGui::InputText(input_b.c_str(), sb.data(), 2); ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_FrameBg, COLOR_GRAY);
            ImGui::InputText(input_a.c_str(), sa.data(), 2); ImGui::SameLine();
            ImGui::PopStyleColor(4);
            ImGui::PopItemWidth();

            int ir = std::atoi(sr.c_str());
            int ig = std::atoi(sg.c_str());
            int ib = std::atoi(sb.c_str());
            int ia = std::atoi(sa.c_str());

            th.bits.r = (sr[0] == '-' || ir < 0)
                ? -1 : std::min(ir, 7);
            th.bits.g = (sg[0] == '-' || ig < 0)
                ? -1 : std::min(ig, 7);
            th.bits.b = (sb[0] == '-' || ib < 0) 
                ? -1 : std::min(ib, 7);
            th.bits.a = (sa[0] == '-' || ia < 0) 
                ? -1 : std::min(ia, 7);

            ImGui::Spacing();
            ImGui::SameLine();
          
            ImGui::PushItemWidth(128);
            const std::string valstr = "##value_" + std::to_string(idx);
            ImGui::SliderFloat(valstr.c_str(), &th.value, 0, 1);
            ImGui::PopItemWidth();
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.8F, 0.25F, 0.25F, 1));
            if(ImGui::Button((" - ##" + std::to_string(idx)).c_str()))
            {
                delete_idx = idx;
            }
            ImGui::PopStyleColor();
            ImGui::Separator();
           
            th.value = std::clamp(th.value, 0.0F, 1.0F);

            ++idx;
        }

        if(ImGui::Button(" + "))
        {
            _thresholds.push_back(xsteg::availability_threshold());
        }
    }
    ImGui::EndChild();
}

xsteg::pixel_availability threshold_editor::truncated_bits()
{
    xsteg::pixel_availability result;
    auto it_r = std::max_element(_thresholds.begin(), _thresholds.end(), 
        [](const auto& th1, const auto& th2) -> bool { return th1.bits.r > th2.bits.r; });
    auto it_g = std::max_element(_thresholds.begin(), _thresholds.end(), 
        [](const auto& th1, const auto& th2) -> bool { return th1.bits.g > th2.bits.g; });
    auto it_b = std::max_element(_thresholds.begin(), _thresholds.end(), 
        [](const auto& th1, const auto& th2) -> bool { return th1.bits.b > th2.bits.b; });
    auto it_a = std::max_element(_thresholds.begin(), _thresholds.end(), 
        [](const auto& th1, const auto& th2) -> bool { return th1.bits.a > th2.bits.a; });

    result.r = (it_r != _thresholds.end()) ? std::max(0, it_r->bits.r) : 0;
    result.g = (it_g != _thresholds.end()) ? std::max(0, it_g->bits.g) : 0;
    result.b = (it_b != _thresholds.end()) ? std::max(0, it_b->bits.b) : 0;
    result.a = (it_a != _thresholds.end()) ? std::max(0, it_a->bits.a) : 0;
    return result;
}