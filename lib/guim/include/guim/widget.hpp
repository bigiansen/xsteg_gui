#pragma once

#include <imgui.h>

namespace guim
{
    class widget
    {
    protected:
        bool _enabled = true;
        ImVec2 _size = { 0, 0 };

    public:
        widget(ImVec2 size = ImVec2(0, 0));

        void enable(bool enable) noexcept;
        bool enabled() const noexcept;

        void set_size(ImVec2 sz) noexcept;

        virtual void update() = 0;
    };
}