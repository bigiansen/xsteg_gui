#pragma once

#include <guim/button.hpp>
#include <guim/msg_popup.hpp>
#include <guim/text_input.hpp>
#include <guim/window.hpp>
#include "browse_popup.hpp"
#include "restore_key_popup.hpp"
#include "threshold_editor.hpp"

class encode_window final : public guim::window
{
private:
    // -- Widgets --
    guim::text_input* _ti_input_image = nullptr;
    guim::text_input* _ti_output_image = nullptr;
    guim::text_input* _ti_data_file = nullptr;
    guim::button* _btn_browse_ii = nullptr;
    guim::button* _btn_browse_oi = nullptr;
    guim::button* _btn_browse_df = nullptr;
    threshold_editor* _th_editor = nullptr;
    guim::button* _btn_gen_key = nullptr;
    guim::button* _btn_restore_key = nullptr;
    browse_popup* _bp_input_image = nullptr;
    browse_popup* _bp_output_image = nullptr;
    browse_popup* _bp_data_file = nullptr;
    guim::msg_popup* _msgp_gen_key = nullptr;
    restore_key_popup* _msgp_res_key = nullptr;
    
public:
    encode_window(ImVec2 size = ImVec2(0, 0));
    void update() override;
};