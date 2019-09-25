#include "encode_window.hpp"

#include <guim/msg_popup.hpp>
#include <guim/separator.hpp>
#include <guim/type_traits.hpp>
#include <strutils/strutils.hpp>
#include <xsteg/steganographer.hpp>
#include "browse_popup.hpp"
#include <fstream>

using namespace std::string_literals;

encode_window::encode_window(ImVec2 sz)
    : window("encode_window", sz)
{
    _ti_input_image = add_widget<guim::text_input>("##ti_ii");
    _ti_input_image->sameline = true;
    _btn_browse_ii = add_widget<guim::button>("Browse...##_ii");

    _ti_output_image = add_widget<guim::text_input>("##ti_oi");
    _ti_output_image->sameline = true;
    _btn_browse_oi = add_widget<guim::button>("Browse...##_oi");

    _ti_data_file = add_widget<guim::text_input>("##ti_df");
    _ti_data_file->sameline = true;
    _btn_browse_df = add_widget<guim::button>("Browse...##_df");

    _th_editor = add_widget<threshold_editor>("##threshold_editor");
    _th_editor->border_enabled = true;
    _th_editor->set_size(ImVec2(0, _size.y - 152));

    _btn_gen_key = add_widget<guim::button>("Generate Key");
    _btn_gen_key->sameline = true;
    _btn_restore_key = add_widget<guim::button>("Restore Key");

    add_widget<guim::separator>();

    _btn_encode = add_widget<guim::button>("Encode##000");

    const ImVec2 browse_popup_size = ImVec2(_size.x * 0.8F, _size.y * 0.8F);

	_ti_input_image->set_text_change_callback([this](const std::string& text)
	{
		_th_editor->set_input_image(text);
	});

    _bp_input_image = add_widget<browse_popup>(
        "Browse##,ii", 
        browse_popup_mode::FILE_SELECT, 
        &_ti_input_image->text(),
        browse_popup_size
    );
    _bp_output_image = add_widget<browse_popup>(
        "Browse##,oi",
        browse_popup_mode::FILE_SAVE,
        &_ti_output_image->text(),
        browse_popup_size
    );
    _bp_data_file = add_widget<browse_popup>(
        "Browse##,df", 
        browse_popup_mode::FILE_SELECT, 
        &_ti_data_file->text(),
        browse_popup_size
    );

    _msgp_gen_key = add_widget<guim::msg_popup>(
        "Generated Key",
        "",
        true,
        ImVec2(0, 0)
    );

    _msgp_res_key = add_widget<restore_key_popup>(
        "Restore key", 
        _th_editor->thresholds(),
        ImVec2(240, 96)
    );
    _msgp_res_key->set_callback([&]()
    {
        _th_editor->regenerate_thresholds();
    });
    
    _btn_browse_ii->add_callback([&](){ _bp_input_image->show(); });
    _btn_browse_oi->add_callback([&](){ _bp_output_image->show(); });
    _btn_browse_df->add_callback([&](){ _bp_data_file->show(); });
    _btn_gen_key->add_callback([&]()
    {
        std::string key = xsteg::generate_thresholds_key(_th_editor->thresholds());
        _msgp_gen_key->set_text(std::move(key));
        _msgp_gen_key->show();
    });
    _btn_restore_key->add_callback([&]()
    {
        _msgp_res_key->show();
    });

    _btn_encode->add_callback([&]()
    {
        static guim::msg_popup* _err_pp = 
            add_widget<guim::msg_popup>("Error", "");

        _ti_input_image->set_text(std::string(strutils::trim(_ti_input_image->text())));
        _ti_output_image->set_text(std::string(strutils::trim(_ti_output_image->text())));
        _ti_data_file->set_text(std::string(strutils::trim(_ti_data_file->text())));

        if(!stdfs::exists(_ti_input_image->text())) 
        { _err_pp->show("Invalid input file!"); return; }
        if(!(_ti_output_image->text().size() > 0)) 
        { _err_pp->show("Invalid output file!"); return; }
        if(!stdfs::exists(_ti_data_file->text())) 
        { _err_pp->show("Invalid data file!"); return; }
        if(_th_editor->thresholds().empty()) 
        { _err_pp->show("No thresholds set!"); return; }

        xsteg::steganographer steg(_ti_input_image->text());
        for(auto& th : _th_editor->thresholds())
        {
            steg.add_threshold(th.data_type, th.direction, th.value, th.bits);
        }
        
        std::ifstream ifs_data(_ti_data_file->text(), std::ios::binary);
        ifs_data.seekg(std::ios_base::end);
        auto sz = ifs_data.tellg();
        std::vector<uint8_t> data;
        data.resize(sz, 0);
        if(ifs_data)
        {
            ifs_data.read((char*)data.data(), sz);
        }
        steg.write_data(data.data(), data.size());
        steg.save_to_file(_ti_output_image->text());
    });
}

void encode_window::update()
{
    static bool first_time = true;

    if(first_time)
    {
        first_time = false;
    }
    
    ImVec2 win_sz = get_current_window_sz();
    ImVec2 input_size(win_sz.x -94, win_sz.y);

    _ti_input_image->set_size(input_size);
    _ti_output_image->set_size(input_size);
    _ti_data_file->set_size(input_size);

    _th_editor->set_size(ImVec2(0, win_sz.y - 154));

    window::update();
}