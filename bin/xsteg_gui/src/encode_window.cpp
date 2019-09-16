#include "encode_window.hpp"

#include <guim/msg_popup.hpp>
#include <guim/type_traits.hpp>
#include "browse_popup.hpp"

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
    _th_editor->set_size(ImVec2(0, _size.y - 128));

    _btn_gen_key = add_widget<guim::button>("Generate Key");
    _btn_gen_key->sameline = true;
    _btn_restore_key = add_widget<guim::button>("Restore Key");

    const ImVec2 browse_popup_size = ImVec2(_size.x * 0.8F, _size.y * 0.8F);

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

    auto ff = "asdf";
    static_assert(guim::tt::is_cstring<decltype(ff)>);

    _msgp_gen_key = add_widget<guim::msg_popup>(
        "Generated Key",
        "",
        true,
        ImVec2(0, 0)
    );
    
    _btn_browse_ii->add_callback([&](){ _bp_input_image->show(); });
    _btn_browse_oi->add_callback([&](){ _bp_output_image->show(); });
    _btn_browse_df->add_callback([&](){ _bp_data_file->show(); });
    _btn_gen_key->add_callback([&]()
    {
        std::string key = xsteg::generate_thresholds_key(_th_editor->thresholds());
        _msgp_gen_key->set_text(std::move(key));
        _msgp_gen_key->show();
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

    _th_editor->set_size(ImVec2(0, win_sz.y - 128));

    window::update();
}