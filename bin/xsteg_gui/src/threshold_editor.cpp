#include "threshold_editor.hpp"

#include <guim/button.hpp>
#include <guim/color.hpp>
#include <guim/combo.hpp>
#include <guim/separator.hpp>
#include <guim/text.hpp>
#include <guim/text_input.hpp>

const static guim::color COLOR_RED(0.5F, 0.2F, 0.2F, 1.0F);
const static guim::color COLOR_GREEN(0.2F, 0.5F, 0.2F, 1.0F);
const static guim::color COLOR_BLUE(0.2F, 0.2F, 0.5F, 1.0F);
const static guim::color COLOR_GRAY(0.3F, 0.3F, 0.3F, 1.0F);

static std::array<std::string, 9> data_types = {
    "VALUE_RED",    "VALUE_GREEN",  "VALUE_BLUE", 
    "SATURATION",   "LUMINANCE",    "SATURATION",
    "ALPHA",        "AVERAGE_RGBA", "AVERAGE_RGB"
};

static const std::array<std::string, 2> directions = {
    "UP",
    "DOWN"
};

threshold_view::threshold_view(
    const std::string& label,
    xsteg::availability_threshold* thres,
    int thres_idx,
    ImVec2 sz)
    : frame(label, sz)
    , _threshold(thres)
    , threshold_idx(thres_idx)
{
    // Index label
    guim::text* idx_label = add_widget<guim::text>("[" + std::to_string(threshold_idx) +"]:");
    idx_label->sameline = true;
    
    // Data type combo
    std::string dt_combo_label = "##data_type_combo_" + std::to_string(threshold_idx);
    guim::combo* combo_dt = add_widget<guim::combo>(dt_combo_label, (int*)&_threshold->data_type);
    combo_dt->add_items(data_types);
    combo_dt->set_size(ImVec2(96, 0));
    combo_dt->sameline = true;

    // Direction combo
    std::string dir_combo_label = "##direction_combo_" + std::to_string(threshold_idx);
    guim::combo* combo_dir = add_widget<guim::combo>(dir_combo_label, (int*)&_threshold->direction);
    combo_dir->add_items(directions);
    combo_dir->set_size(ImVec2(60, 0));
    combo_dir->sameline = true;

    // Bit selectors
    std::string bit_r_label = "##bit_r_" + std::to_string(threshold_idx);
    guim::text_input* bit_r = add_widget<guim::text_input>(bit_r_label, 1);
    bit_r->sameline = true;
    bit_r->set_size(ImVec2(16, 0));
    bit_r->background_color = COLOR_RED;

    std::string bit_g_label = "##bit_g_" + std::to_string(threshold_idx);
    guim::text_input* bit_g = add_widget<guim::text_input>(bit_g_label, 1);
    bit_g->sameline = true;
    bit_g->set_size(ImVec2(16, 0));
    bit_g->background_color = COLOR_GREEN;

    std::string bit_b_label = "##bit_b_" + std::to_string(threshold_idx);
    guim::text_input* bit_b = add_widget<guim::text_input>(bit_b_label, 1);
    bit_b->sameline = true;
    bit_b->set_size(ImVec2(16, 0));
    bit_b->background_color = COLOR_BLUE;


    std::string bit_a_label = "##bit_a_" + std::to_string(threshold_idx);
    guim::text_input* bit_a = add_widget<guim::text_input>(bit_a_label, 1);
    bit_a->sameline = true;
    bit_a->set_size(ImVec2(16, 0));
    bit_a->background_color = COLOR_GRAY;
}

void threshold_view::update()
{
    container::update();

    // ImGui::SameLine();
    // ImGui::Spacing();
    // ImGui::SameLine();

    // const std::string input_r = "##r_" + std::to_string(threshold_idx);
    // const std::string input_g = "##g_" + std::to_string(threshold_idx);
    // const std::string input_b = "##b_" + std::to_string(threshold_idx);
    // const std::string input_a = "##a_" + std::to_string(threshold_idx);

    // std::string sr = (_threshold->bits.r <= -1)
    //     ? "-" : std::to_string(std::clamp(_threshold->bits.r, 0, 7));
    // std::string sg = (_threshold->bits.g <= -1)
    //     ? "-" : std::to_string(std::clamp(_threshold->bits.g, 0, 7));
    // std::string sb = (_threshold->bits.b <= -1)
    //     ? "-" : std::to_string(std::clamp(_threshold->bits.b, 0, 7));
    // std::string sa = (_threshold->bits.a <= -1)
    //     ? "-" : std::to_string(std::clamp(_threshold->bits.a, 0, 7));

    // ImGui::PushItemWidth(16);
    // ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_FrameBg, COLOR_RED);
    // ImGui::InputText(input_r.c_str(), sr.data(), 2); ImGui::SameLine();
    // ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_FrameBg, COLOR_GREEN);
    // ImGui::InputText(input_g.c_str(), sg.data(), 2); ImGui::SameLine();
    // ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_FrameBg, COLOR_BLUE);
    // ImGui::InputText(input_b.c_str(), sb.data(), 2); ImGui::SameLine();
    // ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_FrameBg, COLOR_GRAY);
    // ImGui::InputText(input_a.c_str(), sa.data(), 2); ImGui::SameLine();
    // ImGui::PopStyleColor(4);
    // ImGui::PopItemWidth();

    // int ir = std::atoi(sr.c_str());
    // int ig = std::atoi(sg.c_str());
    // int ib = std::atoi(sb.c_str());
    // int ia = std::atoi(sa.c_str());

    // _threshold->bits.r = (sr[0] == '-' || ir < 0)
    //     ? -1 : std::min(ir, 7);
    // _threshold->bits.g = (sg[0] == '-' || ig < 0)
    //     ? -1 : std::min(ig, 7);
    // _threshold->bits.b = (sb[0] == '-' || ib < 0) 
    //     ? -1 : std::min(ib, 7);
    // _threshold->bits.a = (sa[0] == '-' || ia < 0) 
    //     ? -1 : std::min(ia, 7);

    ImGui::Spacing();
    ImGui::SameLine();
    
    ImGui::PushItemWidth(128);
    const std::string valstr = "##value_" + std::to_string(threshold_idx);
    ImGui::SliderFloat(valstr.c_str(), &_threshold->value, 0, 1);
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.8F, 0.25F, 0.25F, 1));
    if(ImGui::Button((" - ##" + std::to_string(threshold_idx)).c_str()))
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
    for(auto& th_view : _threshold_views)
    {
        if(th_view->delete_pending)
        {
            int idx = th_view->threshold_idx;
            _thresholds.erase(_thresholds.begin() + idx);
            _regen = true;
            break;
        }
    }

    if(_regen)
    {
        _regen = false;
        _widgets.clear();
        _threshold_views.clear();

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
            _regen = true;
        };
    }

    frame::update();
}
