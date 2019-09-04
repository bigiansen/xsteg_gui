#include "fopen_window.hpp"

#include <xsteg/image.hpp>
#include <filesystem>

fopen_window::fopen_window(application_window* wnd, const std::string& title, std::string* dest_str)
    : imgui_window(wnd, title)
    , _dest_str(dest_str)
{ }

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
        std::string str = "[+] " + dir.first.filename().string();
        bool selected = false;
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
        ImGui::Selectable(str.c_str(), &selected);
        if(selected)
        {
            *_dest_str = dir.first.string();
            _show = false;
        }
    }
}