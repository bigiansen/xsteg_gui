#include "browse_popup.hpp"

#include <imgui_stdlib.h>
#include <guim/button.hpp>
#include <guim/msg_popup.hpp>
#include <guim/selectable.hpp>

#include <set>

#define stdfs std::filesystem

browse_popup::browse_popup(const std::string& label, browse_popup_mode mode, std::string* target, ImVec2 size)
    : container(size)
    , _mode(mode)
    , _label(label)
    , _target(target)
{ }

const std::string& browse_popup::selected()
{
    return _selected_text;
}

void browse_popup::update()
{
    if(_first_update)
    {
        _current_dir = stdfs::current_path();
        _requires_refresh = true;
        _first_update = false;
    }
    
    if(enabled)
    {
        if(_requires_refresh)
        {
            _requires_refresh = false;
            _widgets.clear();
            refresh_current_directory();
            ImGui::BeginChild("##file_list", ImVec2(0, 0), true);
            {
                setup_directory_widgets();
                setup_file_widgets();
            }
            ImGui::EndChild();
        }

        ImGuiWindowFlags flags = 0;
        flags |= ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize;
        ImGui::SetNextWindowSize(_size);
        if(ImGui::BeginPopupModal(_label.c_str(), NULL, flags))
        {
            #ifdef _WIN32
            update_drive_selector();
            #endif
            if(ImGui::ArrowButton("##dir_up", ImGuiDir_Up))
            {
                _current_dir = _current_dir.parent_path();
                _requires_refresh = true;
            }
            ImGui::SameLine();
            ImGui::Text(_current_dir.string().c_str());
            ImGui::Separator();

            container::update();

            if(_mode == browse_popup_mode::FILE_SAVE)
            {
                ImGui::Separator();
                ImGui::InputText(_label.c_str(), &_selected_text);
                ImGui::SameLine();
                if(ImGui::Button("Save"))
                {
                    ImGui::CloseCurrentPopup();
                    *_target = (_current_dir / _selected_text).string();
                };
            }
            ImGui::EndPopup();
        }
    }
}

void browse_popup::show()
{
    ImGui::OpenPopup(_label.c_str());
}

void browse_popup::refresh_current_directory()
{
    _current_dirs.clear();
    _current_files.clear();
    static std::set<stdfs::path> banned_paths;
    auto options = stdfs::directory_options::skip_permission_denied;
    try
    {
        for(auto& entry : stdfs::directory_iterator(_current_dir, options))
        {
            if(banned_paths.count(entry)) { continue; }
            try
            {
                if(stdfs::is_directory(entry))
                {
                    _current_dirs.push_back(entry);
                }
                else if(stdfs::is_regular_file(entry))
                {
                    _current_files.push_back(entry);
                }
            }
            catch(std::filesystem::filesystem_error)
            {
                banned_paths.emplace(entry);
            }
        }
    }
    catch(stdfs::filesystem_error e)
    {
        exit(e.code().value());
    }
}

void browse_popup::setup_directory_widgets()
{
    for(auto& dir : _current_dirs)
    {
        auto* ptr = add_widget<guim::selectable>(dir.filename().string().c_str());
        ptr->add_callback([&]()
        {
            _current_dir = dir;
            _requires_refresh = true;
        });
    }
}

void browse_popup::setup_file_widgets()
{    
    for(auto& file : _current_files)
    {
        auto* ptr = add_widget<guim::selectable>(file.filename().string().c_str());
        ptr->color_background = guim::color(0, 0, 0, 0);
        ptr->add_callback([&]()
        {
            if(_mode == browse_popup_mode::FILE_SELECT)
            {
                _selected_text = file.filename().string().c_str();
                _requires_refresh = true;
                ImGui::CloseCurrentPopup();
                *_target = (_current_dir / _selected_text).string();
            }
            else if(_mode == browse_popup_mode::FILE_SAVE)
            {
                _selected_text = file.filename().string().c_str();
            }
        });
    }
}

#ifdef _WIN32
#include <Windows.h>

void browse_popup::update_drive_selector()
{
    DWORD mask = GetLogicalDrives();
    static const std::string LETTERS = "abcdefghijklmnopqrstuvwxyz";
    static std::string available_drives;
    available_drives.clear();
    for(size_t i = 0; i < LETTERS.size(); ++i)
    {
        DWORD check_mask = 0 | (1 << i);
        if((mask | check_mask) == mask)
        {
            std::string path = std::string("") + LETTERS[i] + ":";
            INT type = GetDriveTypeA(path.c_str());
            
            if(type == DRIVE_REMOVABLE || type == DRIVE_FIXED)
            {
                available_drives += LETTERS[i];
                available_drives += '\0';
            }
        }
    }

    static int current_item = 0;
    auto* data = available_drives.data();
    ImGui::SetNextItemWidth(40);
    ImGui::Text("Drive: ");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(40);
    if(ImGui::Combo("##drives", &current_item, data, available_drives.size()))
    {
        std::string path = "";
        path += available_drives[current_item * 2];
        path += ":\\";        
        _current_dir = stdfs::path(path);
        _requires_refresh = true;
    }
    ImGui::SameLine();
}

#endif