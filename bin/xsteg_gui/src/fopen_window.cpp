#include "fopen_window.hpp"

#include <xsteg/image.hpp>
#include <stb_image.h>
#include <filesystem>
#include <exception>
#include <iostream>
#include <set>

std::optional<GLuint> fopen_window::_tex_folder;
std::optional<GLuint> fopen_window::_tex_file;

GLuint upload_image_tex2d(const xsteg::image& img)
{
    static const int pfmt = GL_RGBA; // pixel format
    static const int pcdt = GL_UNSIGNED_BYTE; // channel data type
    static const auto target = GL_TEXTURE_2D; // gl texture target
    static const int tex_filter = GL_NEAREST; // texture filtering method

    GLuint result;

    auto w = img.width();
    auto h = img.height();

    glGenTextures(1, &result);
    glBindTexture(target, result);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, tex_filter);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, tex_filter);
    glTexImage2D(target, 0, pfmt, w, h, 0, pfmt, pcdt, img.cdata());

    return result;
}

fopen_window::fopen_window(application_window* wnd, const std::string& title, std::string* dest_str)
    : imgui_window(wnd, title)
    , _dest_str(dest_str)
{
    init_textures();
}

void fopen_window::init_textures()
{
    if(!_tex_folder || !_tex_file)
    {
        _tex_folder = 0;
        _tex_file = 0;

        xsteg::image img_folder("res/folder.png");
        xsteg::image img_file("res/file.png");

        _tex_folder = upload_image_tex2d(img_folder);
        _tex_file = upload_image_tex2d(img_file);
    }
}

void fopen_window::update_proc()
{
    static auto cur_path = std::filesystem::current_path();
    static std::map<std::filesystem::path, bool> current_dirs;
    static std::map<std::filesystem::path, bool> current_files;

    if(ImGui::ArrowButton("UP", ImGuiDir_::ImGuiDir_Up))
    {
        cur_path = cur_path.parent_path();
        current_dirs.clear();
        current_files.clear();
    }
    
    ImGui::SameLine();
    ImGui::Text(cur_path.string().c_str());
    ImGui::Separator();

    for(auto& entry : std::filesystem::directory_iterator(cur_path))
    {
        static std::set<std::string> banned_entries;
        std::string str = entry.path().string();
        if(banned_entries.count(str)) { continue; }
        try
        {
            if (std::filesystem::is_directory(entry))
            {
                current_dirs.emplace(entry.path(), false);
            }
            else
            {
                current_files.emplace(entry.path(), false);
            }
        }
        catch(const std::filesystem::filesystem_error& e)
        {
            banned_entries.emplace(str);
            std::cout << "Skipped file: " << str << std::endl;
            std::cout << "Exception: [" << e.code() << "] " << e.what() << std::endl; 
            continue;
        }
    }

    for(auto& dir : current_dirs)
    {
        std::string str = dir.first.filename().string();
        bool selected = false;
        ImGui::Image((void*)(intptr_t)(*_tex_folder), ImVec2(16, 16));
        ImGui::SameLine();
        ImGui::Selectable(str.c_str(), &selected);
        if(selected)
        {
            cur_path = dir.first;
            current_files.clear();
            current_dirs.clear();
            return;
        }
    }

    for(auto& dir : current_files)
    {
        std::string str = dir.first.filename().string();
        bool selected = false;
        ImGui::Image((void*)(intptr_t)(*_tex_file), ImVec2(16, 16));
        ImGui::SameLine();
        ImGui::Selectable(str.c_str(), &selected);
        if(selected)
        {
            *_dest_str = dir.first.string();
            _show = false;
        }
    }
}