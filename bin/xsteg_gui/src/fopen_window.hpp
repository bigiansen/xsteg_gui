#pragma once

#include <imgui.h>
#include <string>
#include <xsteg/image.hpp>

#include "imgui_window.hpp"

class fopen_window final : public imgui_window
{
private:
    std::string* _dest_str;

public:
    fopen_window(application_window*, const std::string& title, std::string* dest_str);

protected:
    void update_proc() override;
};