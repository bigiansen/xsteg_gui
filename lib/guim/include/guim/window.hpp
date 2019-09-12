#pragma once

#include <guim/container.hpp>
#include <optional>
#include <string>

namespace guim
{
    class window : public container
    {
    protected:
        std::string _name;
        std::optional<ImVec2> _position;
        ImVec2 _current_window_sz;

    public:
        bool background = true;
        bool titlebar = true;
        bool resizable = true;
        bool never_on_front = false;

        window(const std::string& name, ImVec2 size = ImVec2(0, 0));
        
        void set_position(ImVec2 pos);
        void reset_position();

        ImVec2 get_current_window_sz();
        
        void update() override;
    };
}