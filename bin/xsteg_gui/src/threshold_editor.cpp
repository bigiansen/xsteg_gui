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

void threshold_preview_popup::set_input_image(const std::string& fname)
{
	_input_image = std::make_unique<xsteg::image>(fname);
}

void threshold_preview_popup::update()
{
	if(!enabled) { return; }
	if(!_input_image) { return; }
	if(!_image_initialized)
	{
		xsteg::image preview_img = xsteg::generate_visual_data_diff_image(
			_input_image.get(),
			_threshold->data_type,
			_threshold->value,
			_threshold->bits);

		_image_widget->load_from_image(
			"_th_preview_popup_",
			preview_img.cdata(),
			preview_img.width(),
			preview_img.height());
		_image_widget->set_size(ImVec2(400, 400));

		_image_initialized = true;
	}

	background_color.push();
	foreground_color.push();
	if(ImGui::BeginPopupModal(_name.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		container::update();
		if(ImGui::Button("Close"))
		{
			ImGui::CloseCurrentPopup();
			_image_initialized = false;
		}
		ImGui::EndPopup();
	}
	background_color.pop();
	foreground_color.pop();
}

threshold_view::threshold_view(
	const std::string& label,
	threshold_editor* parent,
	xsteg::availability_threshold* thres,
	int thres_idx,
	ImVec2 sz)
	: frame(label, sz)
	, _parent(parent)
	, _threshold(thres)
	, threshold_idx(thres_idx)
{
	init_widgets();
}

void threshold_view::init_widgets()
{
	std::string th_suffix = std::to_string(threshold_idx);

	// -- Index label --
	guim::text* idx_label = add_widget<guim::text>("[" + th_suffix + "]:");
    idx_label->set_size(ImVec2(32, 0));
	idx_label->sameline = true;

	// -- Data type combo --
	std::string dt_combo_label = "##data_type_combo_" + th_suffix;
	_combo_data_type = add_widget<guim::combo>(std::move(dt_combo_label), 0);
	_combo_data_type->add_items(data_types);
	_combo_data_type->set_size(ImVec2(96, 0));
	_combo_data_type->sameline = true;

	// -- Direction combo --
	std::string dir_combo_label = "##direction_combo_" + th_suffix;
	_combo_direction = add_widget<guim::combo>(std::move(dir_combo_label), 0);
	_combo_direction->add_items(directions);
	_combo_direction->set_size(ImVec2(60, 0));
	_combo_direction->sameline = true;

	// -- Bit selectors --
	// [R]
	std::string bit_r_label = "##bit_r_" + th_suffix;
	_txt_bit_r = add_widget<guim::text_input>(std::move(bit_r_label), 1);
	_txt_bit_r->sameline = true;
	_txt_bit_r->set_size(ImVec2(16, 0));
	_txt_bit_r->background_color = COLOR_RED;
	_txt_bit_r->set_text("-");

	// [G]
	std::string bit_g_label = "##bit_g_" + th_suffix;
	_txt_bit_g = add_widget<guim::text_input>(std::move(bit_g_label), 1);
	_txt_bit_g->sameline = true;
	_txt_bit_g->set_size(ImVec2(16, 0));
	_txt_bit_g->background_color = COLOR_GREEN;
	_txt_bit_g->set_text("-");

	// [B]
	std::string bit_b_label = "##bit_b_" + th_suffix;
	_txt_bit_b = add_widget<guim::text_input>(std::move(bit_b_label), 1);
	_txt_bit_b->sameline = true;
	_txt_bit_b->set_size(ImVec2(16, 0));
	_txt_bit_b->background_color = COLOR_BLUE;
	_txt_bit_b->set_text("-");

	// [A]
	std::string bit_a_label = "##bit_a_" + th_suffix;
	_txt_bit_a = add_widget<guim::text_input>(std::move(bit_a_label), 1);
	_txt_bit_a->sameline = true;
	_txt_bit_a->set_size(ImVec2(16, 0));
	_txt_bit_a->background_color = COLOR_GRAY;
	_txt_bit_a->set_text("-");

	// -- Value slider --
	std::string slider_label = "##value_slider_" + th_suffix;
	_slider_value = add_widget<guim::float_slider>(slider_label, 0.0F, 1.0F, 0.0F);
	_slider_value->set_size(ImVec2(128, 0));
	_slider_value->sameline = true;

	// -- Preview button --
	const std::string preview_button_txt = ("Preview##" + std::to_string(threshold_idx));
	_button_preview = add_widget<guim::button>(preview_button_txt, ImVec2(32, 0));

	_prev_pp = add_widget<threshold_preview_popup>(
		preview_button_txt,
		this,
		_threshold
	);

	_button_preview->add_callback([&]()
	{
		_prev_pp->set_input_image(_parent->input_image());
		_prev_pp->show();
	});
	
	// -- Remove button --
	std::string remove_button_txt = (" - ##" + std::to_string(threshold_idx));
	_button_remove = add_widget<guim::button>(remove_button_txt, ImVec2(32, 0));
	_button_remove->background_color = guim::color(0.8F, 0.25F, 0.25F, 1);
	_button_remove->add_callback([&]()
	{
		delete_pending = true;
	});
}

void threshold_view::update()
{	
	read_values();
	container::update();
	update_values();
}

void threshold_view::read_values()
{
	_combo_data_type->selected_index = (int)_threshold->data_type;
	_combo_direction->selected_index = (int)_threshold->direction;

	std::string bit_r = _threshold->bits.r < 0 ? "-" : std::to_string(_threshold->bits.r);
	std::string bit_g = _threshold->bits.g < 0 ? "-" : std::to_string(_threshold->bits.g);
	std::string bit_b = _threshold->bits.b < 0 ? "-" : std::to_string(_threshold->bits.b);
	std::string bit_a = _threshold->bits.a < 0 ? "-" : std::to_string(_threshold->bits.a);	
	_txt_bit_r->set_text(bit_r);
	_txt_bit_g->set_text(bit_g);
	_txt_bit_b->set_text(bit_b);
	_txt_bit_a->set_text(bit_a);

	_slider_value->value = _threshold->value;
}

void threshold_view::update_values()
{
	using data_type_t = decltype(_threshold->data_type);
	using direction_t = decltype(_threshold->direction);

	_threshold->value = _slider_value->value;
	_threshold->direction = static_cast<direction_t>(_combo_direction->selected_index);
	_threshold->data_type = static_cast<data_type_t>(_combo_data_type->selected_index);
	
	auto get_bit_value = [](const std::string& str) -> int
	{
		if (str.size() == 0)
		{
			return -1;
		}
		char ch = str[0];
		if (ch == '-' || ch == '_')
		{
			return -1;
		}
		return std::clamp(std::atoi(str.c_str()), 0, 7);
	};

	_threshold->bits.r = get_bit_value(_txt_bit_r->text());
	_threshold->bits.g = get_bit_value(_txt_bit_g->text());
	_threshold->bits.b = get_bit_value(_txt_bit_b->text());
	_threshold->bits.a = get_bit_value(_txt_bit_a->text());
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
		regenerate_thresholds();
	}

	frame::update();
}

std::vector<xsteg::availability_threshold>& threshold_editor::thresholds()
{
	return _thresholds;
}

void threshold_editor::regenerate_thresholds()
{
	_regen = false;
	_widgets.clear();
	_threshold_views.clear();

	int idx = 0;
	for (auto& th : _thresholds)
	{
		_threshold_views.push_back(
			add_widget<threshold_view>("##thres_1234" + std::to_string(idx), this, &th, idx)
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
