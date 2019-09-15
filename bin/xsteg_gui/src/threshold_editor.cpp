#include "threshold_editor.hpp"

#include <guim/button.hpp>
#include <guim/color.hpp>
#include <guim/combo.hpp>
#include <guim/float_slider.hpp>
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
    std::string th_suffix = std::to_string(threshold_idx);

    // -- Index label --
    guim::text* idx_label = add_widget<guim::text>("[" + th_suffix +"]:");
    idx_label->sameline = true;
    
    // -- Data type combo --
    std::string dt_combo_label = "##data_type_combo_" + th_suffix;
    guim::combo* combo_dt = add_widget<guim::combo>(dt_combo_label, (int*)&_threshold->data_type);
    combo_dt->add_items(data_types);
    combo_dt->set_size(ImVec2(96, 0));
    combo_dt->sameline = true;

    // -- Direction combo --
    std::string dir_combo_label = "##direction_combo_" + th_suffix;
    guim::combo* combo_dir = add_widget<guim::combo>(dir_combo_label, (int*)&_threshold->direction);
    combo_dir->add_items(directions);
    combo_dir->set_size(ImVec2(60, 0));
    combo_dir->sameline = true;

    // -- Bit selectors --
	// [R]
    std::string bit_r_label = "##bit_r_" + th_suffix;
    guim::text_input* bit_r = add_widget<guim::text_input>(bit_r_label, 1);
    bit_r->sameline = true;
    bit_r->set_size(ImVec2(16, 0));
    bit_r->background_color = COLOR_RED;

	// [G]
    std::string bit_g_label = "##bit_g_" + th_suffix;
    guim::text_input* bit_g = add_widget<guim::text_input>(bit_g_label, 1);
    bit_g->sameline = true;
    bit_g->set_size(ImVec2(16, 0));
    bit_g->background_color = COLOR_GREEN;

	// [B]
    std::string bit_b_label = "##bit_b_" + th_suffix;
    guim::text_input* bit_b = add_widget<guim::text_input>(bit_b_label, 1);
    bit_b->sameline = true;
    bit_b->set_size(ImVec2(16, 0));
    bit_b->background_color = COLOR_BLUE;

	// [A]
    std::string bit_a_label = "##bit_a_" + th_suffix;
    guim::text_input* bit_a = add_widget<guim::text_input>(bit_a_label, 1);
    bit_a->sameline = true;
    bit_a->set_size(ImVec2(16, 0));
    bit_a->background_color = COLOR_GRAY;

	// -- Value slider --
    std::string slider_label = "##value_slider_"  + th_suffix;
	guim::float_slider* slider = add_widget<guim::float_slider>(slider_label, 0.0F, 1.0F, 0.0F);
	slider->set_size(ImVec2(128, 0));
	slider->sameline = true;

	// -- Remove button --
	std::string button_txt = (" - ##" + std::to_string(threshold_idx));
	guim::button* remove_button = add_widget<guim::button>(button_txt, ImVec2(32, 0));
	remove_button->background_color = guim::color(0.8F, 0.25F, 0.25F, 1);
	remove_button->add_callback([&]()
	{
		delete_pending = true;
	});
}

void threshold_view::update()
{
    container::update();
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

        auto* button = add_widget<guim::button>(std::string("+"));
        *button += [&]()
        {
            _thresholds.push_back(xsteg::availability_threshold());
            _regen = true;
        };
    }

    frame::update();
}
