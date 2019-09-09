#include "browse_popup.hpp"

#include <imgui_stdlib.h>
#include <guim/button.hpp>
#include <guim/selectable.hpp>

#define stdfs std::filesystem

browse_popup::browse_popup(const std::string& label, browse_popup_mode mode, ImVec2 size)
    : container(size)
    , _mode(mode)
    , _label(label)
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
            setup_directory_widgets();
            setup_file_widgets();
            if(_mode == browse_popup_mode::FILE_SAVE)
            {
                ImGui::InputText(_label.c_str(), &_selected_text);
                auto* ptr = add_widget<guim::button>("Save");
                ptr->add_callback([&]()
                {
                    ImGui::CloseCurrentPopup();
                });
            }
        }

        ImGuiWindowFlags flags = 0;
        flags |= ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize;

        if(ImGui::BeginPopupModal(_label.c_str()))
        {
            if(ImGui::ArrowButton("##dir_up", ImGuiDir_Up))
            {
                _current_dir = _current_dir.parent_path();
                _requires_refresh = true;
            }
            ImGui::SameLine();
            ImGui::Text(_current_dir.string().c_str());
            ImGui::Separator();
            container::update();
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
    for(auto& entry : stdfs::directory_iterator(_current_dir))
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
        ptr->add_callback([&]()
        {
            if(_mode == browse_popup_mode::FILE_SELECT)
            {
                _selected_text = file.string().c_str();
                _requires_refresh = true;
                ImGui::CloseCurrentPopup();
            }
            else if(_mode == browse_popup_mode::FILE_SAVE)
            {
                _selected_text = file.string().c_str();
            }
        });
    }
}