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

    void window::update()
    {
        static bool first_time = true;
        if(enabled)
        {
            ImGuiWindowFlags flags = 0;
            if(!background) { flags |= ImGuiWindowFlags_NoBackground; }
            if(!titlebar)   { flags |= ImGuiWindowFlags_NoTitleBar; }
            if(!resizable)  { flags |= ImGuiWindowFlags_NoResize; }

            if(first_time)
            {
                first_time = false;
                ImGui::SetNextWindowSize(_size);
            }
            
            ImGui::Begin(_name.c_str(), NULL, flags);
            {
                if(_position) { ImGui::SetWindowPos(*_position); }
                container::update();
            }
            ImGui::End();
        }
    }
}