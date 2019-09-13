#include "threshold_editor.hpp"

#include <guim/button.hpp>
#include <guim/separator.hpp>

threshold_view::threshold_view(
    const std::string& label,
    xsteg::availability_threshold* thres,
    int thres_idx,
    ImVec2 sz)
    : frame(label, sz)
    , _threshold(thres)
    , _threshold_idx(thres_idx)
{ }

const static ImVec4 COLOR_RED(0.5F, 0.2F, 0.2F, 1.0F);
const static ImVec4 COLOR_GREEN(0.2F, 0.5F, 0.2F, 1.0F);
const static ImVec4 COLOR_BLUE(0.2F, 0.2F, 0.5F, 1.0F);
const static ImVec4 COLOR_GRAY(0.3F, 0.3F, 0.3F, 1.0F);

void threshold_view::update()
{
    static char* data_types[] = {
        "VALUE_RED",    "VALUE_GREEN",  "VALUE_BLUE", 
        "SATURATION",   "LUMINANCE",    "SATURATION",
        "ALPHA",        "AVERAGE_RGBA", "AVERAGE_RGB"
    };
    ImGui::Text("[%d]:", _threshold_idx);

    ImGui::PushItemWidth(128);
    std::string combo_label = "##combo_data_type_" + std::to_string(_threshold_idx);
    ImGui::Combo(combo_label.c_str(), (int*)&_threshold->data_type, data_types, 9);
    ImGui::SameLine();

    static const char* directions[2] = {
        "UP",
        "DOWN"
    };

    const std::string dir_label = "##dir_" + std::to_string(_threshold_idx);
    ImGui::Combo(dir_label.c_str(), (int*)&_threshold->direction, directions, 2);
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::Spacing();
    ImGui::SameLine();

    const std::string input_r = "##r_" + std::to_string(_threshold_idx);
    const std::string input_g = "##g_" + std::to_string(_threshold_idx);
    const std::string input_b = "##b_" + std::to_string(_threshold_idx);
    const std::string input_a = "##a_" + std::to_string(_threshold_idx);

    std::string sr = (_threshold->bits.r <= -1)
        ? "-" : std::to_string(std::clamp(_threshold->bits.r, 0, 7));
    std::string sg = (_threshold->bits.g <= -1)
        ? "-" : std::to_string(std::clamp(_threshold->bits.g, 0, 7));
    std::string sb = (_threshold->bits.b <= -1)
        ? "-" : std::to_string(std::clamp(_threshold->bits.b, 0, 7));
    std::string sa = (_threshold->bits.a <= -1)
        ? "-" : std::to_string(std::clamp(_threshold->bits.a, 0, 7));

    ImGui::PushItemWidth(16);
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

    _threshold->bits.r = (sr[0] == '-' || ir < 0)
        ? -1 : std::min(ir, 7);
    _threshold->bits.g = (sg[0] == '-' || ig < 0)
        ? -1 : std::min(ig, 7);
    _threshold->bits.b = (sb[0] == '-' || ib < 0) 
        ? -1 : std::min(ib, 7);
    _threshold->bits.a = (sa[0] == '-' || ia < 0) 
        ? -1 : std::min(ia, 7);

    ImGui::Spacing();
    ImGui::SameLine();
    
    ImGui::PushItemWidth(128);
    const std::string valstr = "##value_" + std::to_string(_threshold_idx);
    ImGui::SliderFloat(valstr.c_str(), &_threshold->value, 0, 1);
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.8F, 0.25F, 0.25F, 1));
    if(ImGui::Button((" - ##" + std::to_string(_threshold_idx)).c_str()))
    {
        delete_pending = true;
    }
    ImGui::PopStyleColor();
    
    _threshold->value = std::clamp(_threshold->value, 0.0F, 1.0F);
}

threshold_editor::threshold_editor(const std::string& label, ImVec2 size)
    : frame(label, size)
{ }

void threshold_editor::update()
{
    bool regen = false;
    _widgets.clear();
    _threshold_views.clear();

    for(auto it = _threshold_views.begin(); it != _threshold_views.end(); ++it)
    {
        if((*it)->delete_pending)
        {
            regen = true;
            auto itv = std::find(_thresholds.begin(), _thresholds.end(), [&](auto& th)
            {
                &th == (*it).get();
            });
            if(itv != _thresholds.end())
            {
                _thresholds.erase(itv);
            }
        }
    }

    if(regen)
    {
        int idx = 0;
        for(auto& th : _thresholds)
        {
            _threshold_views.push_back(
                add_widget<threshold_view>("##thres_1234" + std::to_string(idx), &th, idx)
            );
            add_widget<guim::separator>();
            ++idx;
        }

        auto* button = add_widget<guim::button>("+");
        *button += [&]()
        {
            _thresholds.push_back(xsteg::availability_threshold());
        };
    }

    frame::update();
}
