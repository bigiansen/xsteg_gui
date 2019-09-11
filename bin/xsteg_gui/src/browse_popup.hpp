#pragma once

#include <guim/container.hpp>
#include <filesystem>

enum class browse_popup_mode
{
    FILE_SELECT,
    FILE_SAVE
};

class browse_popup : public guim::container
{
protected:
    std::filesystem::path _current_dir;
    std::vector<std::filesystem::path> _current_files, _current_dirs;
    std::string _label;
    std::string _selected_text;
    browse_popup_mode _mode;
    std::string* _target;
    bool _requires_refresh = false;

public:
    browse_popup(
        const std::string& label, 
        browse_popup_mode, 
        std::string* target, 
        ImVec2 size = ImVec2(0, 0));
        
    void show();
    void update() override;
    const std::string& selected();

protected:
    void refresh_current_directory();
    void setup_directory_widgets();
    void setup_file_widgets();

// Allow selecting Windows drive letters as current path
#ifdef _WIN32    
    void update_drive_selector();
#endif
};