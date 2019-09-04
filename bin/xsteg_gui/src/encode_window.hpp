#pragma once

#include <string>
#include "imgui_window.hpp"

class encode_window final : public imgui_window 
{
private:
    bool _first_time = true;
    std::string _input_image = std::string(512, '\0');
    std::string _output_image = std::string(512, '\0');
    std::string _input_data = std::string(512, '\0');

public:
    encode_window(window*, const std::string& name);
    encode_window(window*, std::string&& name);

    void show() final override;

protected:
    void update_proc() override;
};