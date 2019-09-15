#include <guim/window.hpp>

namespace guim
{
    window::window(const std::string& name, ImVec2 size)
        : _name(name)
        , container(size)
    { }

    void window::set_position(ImVec2 pos)
    {
        _position = pos;
    }

    void window::reset_position()
    {
        _position.reset();
    }

    ImVec2 window::get_current_window_sz()
    {
        return _current_window_sz;
    }

    void window::update()
    {
		if(!enabled) { return; }
        
        ImGuiWindowFlags flags = 0;

        if(!background)     { flags |= ImGuiWindowFlags_NoBackground; }
        if(!titlebar)       { flags |= ImGuiWindowFlags_NoTitleBar; }
        if(!resizable)      { flags |= ImGuiWindowFlags_NoResize; }
        if(never_on_front)  { flags |= ImGuiWindowFlags_NoBringToFrontOnFocus; }

        if(_first_update)
        {
            _first_update = false;
            ImGui::SetNextWindowSize(_size);
        }
            
        ImGui::Begin(_name.c_str(), NULL, flags);
        {
            _current_window_sz = ImGui::GetWindowSize();
            if(_position) { ImGui::SetWindowPos(*_position); }
            container::update();
        }
        ImGui::End();        
    }
}