#pragma once

#include <guim/button.hpp>
#include <guim/combo.hpp>
#include <guim/float_slider.hpp>
#include <guim/frame.hpp>
#include <guim/image.hpp>
#include <guim/popup.hpp>
#include <guim/text_input.hpp>
#include <guim/type_traits.hpp>
#include <xsteg/availability_map.hpp>
#include <vector>

class threshold_view;
class threshold_editor;

class threshold_preview_popup : public guim::popup
{
private:
	threshold_view* _parent = nullptr;
    xsteg::availability_threshold _threshold;
    guim::image* _image_widget;
    std::unique_ptr<xsteg::image> _input_image;
    bool _image_initialized = false;

public:
    template<typename TStr, typename = guim::tt::enable_if_stringish<TStr>>
	threshold_preview_popup(
		TStr&& label,
		threshold_view* parent,
        xsteg::availability_threshold threshold,
        ImVec2 sz = ImVec2(0, 0))
        : popup(label, sz)
		, _parent(parent)
        , _threshold(threshold)
    { 
        _image_widget = add_widget<guim::image>("##img_thresh_preview" + label);
    }

    void set_input_image(const std::string& filename);
    void update() override;
};

class threshold_view : public guim::frame
{
private:
	threshold_editor* _parent = nullptr;
    xsteg::availability_threshold* _threshold = nullptr;
	guim::combo* _combo_data_type = nullptr;
	guim::combo* _combo_direction = nullptr;
	guim::text_input* _txt_bit_r = nullptr;
	guim::text_input* _txt_bit_g = nullptr;
	guim::text_input* _txt_bit_b = nullptr;
	guim::text_input* _txt_bit_a = nullptr;
	guim::float_slider* _slider_value = nullptr;
    guim::button* _button_preview = nullptr;
	guim::button* _button_remove = nullptr;

public:
    bool delete_pending = false;
    int threshold_idx = -1;    

    threshold_view(
        const std::string& label,
		threshold_editor* parent,
        xsteg::availability_threshold* thres,
        int thres_idx,
        ImVec2 size = ImVec2(0, 0));

	void init_widgets();
    void update() override;

private:
	void update_values();
    void read_values();
};

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

class threshold_editor : public guim::frame
{
private:
    std::vector<xsteg::availability_threshold> _thresholds;
    std::vector<threshold_view*> _threshold_views;
	std::string _iimage;
    bool _regen = true;

public:
    threshold_editor(const std::string& label, ImVec2 size = ImVec2(0, 0));

    void update() override;

    std::vector<xsteg::availability_threshold>& thresholds();
	void regenerate_thresholds();

	void set_input_image(const std::string& ii) { _iimage = ii; }
	const std::string input_image() { return _iimage; }
};