#pragma once

#include <guim/color.hpp>
#include <optional>

namespace guim::traits
{
    class foreground_color
    {
    protected:
        std::optional<color> _fg_color;

    public:
        void set_foreground_color(const color& col) noexcept;
        void reset_foreground_color() noexcept;

        color get_foreground_color() const noexcept;

        void push_foreground_color();
        void pop_foreground_color();
    };
}