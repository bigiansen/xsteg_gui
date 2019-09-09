#pragma once

#include <imgui.h>

namespace guim
{
    class widget
    {
    protected:
        ImVec2 _size = { 0, 0 };

    public:
        bool enabled = true;
        bool sameline = false;

        widget(ImVec2 size = ImVec2(0, 0));

        void set_size(ImVec2 sz) noexcept;

        virtual void update() = 0;
    };
}