#pragma once

#include <imgui.h>
#include <string>
#include <optional>
#include <filesystem>

#include "imgui_window.hpp"

enum class browser_window_mode
{
    FILE_SELECT,
    DIRECTORY_SELECT,
    FILE_SAVE
};

class browser_window : public imgui_window
{
private:
    std::string* _dest_str;
    std::string _selected_text = std::string(512, 0);
    browser_window_mode _mode;

    static std::optional<GLuint> _tex_folder;
    static std::optional<GLuint> _tex_file;

public:
    browser_window(application_window*, const std::string& title, std::string* dest_str, browser_window_mode);

protected:
    virtual void update_proc() override;

private:
    void init_textures();
};