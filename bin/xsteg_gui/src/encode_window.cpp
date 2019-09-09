#include "encode_window.hpp"

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