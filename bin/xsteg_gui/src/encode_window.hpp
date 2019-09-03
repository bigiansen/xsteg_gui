#pragma once

#include "imgui_window.hpp"

class encode_window final : public imgui_window 
{
private:
    bool _first_time = true;

public:
    encode_window(window*, const std::string& name);
    encode_window(window*, std::string&& name);

    void show() final override;

protected:
    void update_proc() override;
};