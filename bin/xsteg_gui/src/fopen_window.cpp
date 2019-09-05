#include "fopen_window.hpp"

#include <xsteg/image.hpp>
#include <stb_image.h>
#include <filesystem>

std::optional<GLuint> fopen_window::_tex_folder;
std::optional<GLuint> fopen_window::_tex_file;

fopen_window::fopen_window(application_window* wnd, const std::string& title, std::string* dest_str)
    : imgui_window(wnd, title)
    , _dest_str(dest_str)
{
    if(!_tex_folder || !_tex_file)
    {
        _tex_folder = 0;
        _tex_file = 0;

        int x, y, ch;

        auto* data = stbi_load("res/folder.png", &x, &y, &ch, STBI_rgb_alpha);
        glGenTextures(1, &_tex_folder.value());
        glBindTexture(GL_TEXTURE_2D, _tex_folder.value());
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);

        data = stbi_load("res/file.png", &x, &y, &ch, STBI_rgb_alpha);
        glGenTextures(1, &_tex_file.value());
        glBindTexture(GL_TEXTURE_2D, _tex_file.value());
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
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

    for(auto& path : std::filesystem::directory_iterator(cur_path))
    {        
        if (std::filesystem::is_directory(path))
        {
            current_dirs.emplace(path.path(), false);
        }
        else
        {
            current_files.emplace(path.path(), false);
        }
    }

    for(auto& dir : current_dirs)
    {
        std::string str = dir.first.filename().string();
        bool selected = false;
        ImGui::Image((void*)(intptr_t)_tex_folder.value(), ImVec2(16, 16));
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
        ImGui::Image((void*)(intptr_t)_tex_file.value(), ImVec2(16, 16));
        ImGui::SameLine();
        ImGui::Selectable(str.c_str(), &selected);
        if(selected)
        {
            *_dest_str = dir.first.string();
            _show = false;
        }
    }

    auto yes = glIsTexture(_tex_folder.value());
}