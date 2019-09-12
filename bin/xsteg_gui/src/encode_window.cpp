#include "encode_window.hpp"

#include <guim/msg_popup.hpp>
#include "browse_popup.hpp"

encode_window::encode_window(ImVec2 sz)
    : window("encode_window", sz)
{ 
    _ti_input_image = add_widget<guim::text_input>("##ti_ii");
    _btn_browse_ii = add_widget<guim::button>("Browse...##_ii");
    _ti_output_image = add_widget<guim::text_input>("##ti_oi");
    _btn_browse_oi = add_widget<guim::button>("Browse...##_oi");
    _ti_data_file = add_widget<guim::text_input>("##ti_df");
    _btn_browse_df = add_widget<guim::button>("Browse...##_df");

    _ti_input_image->sameline = true;
    _ti_output_image->sameline = true;
    _ti_data_file->sameline = true;

    ImVec2 browse_popup_size = ImVec2(_size.x * 0.8F, _size.y * 0.8F);

    static browse_popup* browse_ii = add_widget<browse_popup>(
        "Browse##,ii", 
        browse_popup_mode::FILE_SELECT, 
        &_ti_input_image->text(),
        browse_popup_size
    );
    static browse_popup* browse_oi = add_widget<browse_popup>(
        "Browse##,oi",
        browse_popup_mode::FILE_SAVE,
        &_ti_output_image->text(),
        browse_popup_size
    );
    static browse_popup* browse_df = add_widget<browse_popup>(
        "Browse##,df", 
        browse_popup_mode::FILE_SELECT, 
        &_ti_data_file->text(),
        browse_popup_size
    );
    
    _btn_browse_ii->add_callback([](){ browse_ii->show(); });
    _btn_browse_oi->add_callback([](){ browse_oi->show(); });
    _btn_browse_df->add_callback([](){ browse_df->show(); });
}

void encode_window::update()
{
    static bool first_time = true;

    if(first_time)
    {
        first_time = false;
    }
    
    window::update();
}