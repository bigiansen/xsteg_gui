#pragma once

#include "imgui_window.hpp"

class encode_window final : public imgui_window 
{
public:
    encode_window(window*, const std::string& name);
    encode_window(window*, std::string&& name);

protected:
    void update_proc() override;
};