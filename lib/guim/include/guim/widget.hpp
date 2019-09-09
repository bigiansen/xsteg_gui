#pragma once

#include <imgui.h>

namespace guim
{
    class widget
    {
    protected:
        ImVec2 _size = { 0, 0 };
        bool _first_update = true;
        
    public:
        bool enabled = true;
        bool sameline = false;

        widget(ImVec2 size = ImVec2(0, 0));

        void set_size(ImVec2 sz) noexcept;

        virtual void update() = 0;
    };
}