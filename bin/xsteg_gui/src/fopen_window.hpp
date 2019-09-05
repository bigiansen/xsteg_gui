#pragma once

#include <imgui.h>
#include <string>
#include <optional>

#include "imgui_window.hpp"

class fopen_window final : public imgui_window
{
private:
    std::string* _dest_str;
    static std::optional<GLuint> _tex_folder;
    static std::optional<GLuint> _tex_file;

public:
    fopen_window(application_window*, const std::string& title, std::string* dest_str);

protected:
    void update_proc() override;

private:
    void init_textures();
};