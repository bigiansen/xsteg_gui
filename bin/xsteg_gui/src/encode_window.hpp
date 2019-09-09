#pragma once

#include <guim/button.hpp>
#include <guim/text_input.hpp>
#include <guim/window.hpp>

class encode_window final : public guim::window
{
private:
    guim::text_input* _ti_input_image = nullptr;
    guim::text_input* _ti_output_image = nullptr;
    guim::text_input* _ti_data_file = nullptr;
    guim::button* _btn_browse_ii = nullptr;
    guim::button* _btn_browse_oi = nullptr;
    guim::button* _btn_browse_df = nullptr;
    
public:
    encode_window(ImVec2 size = ImVec2(0, 0));
    void update() override;
};