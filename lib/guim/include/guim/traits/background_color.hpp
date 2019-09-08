#pragma once

#include <guim/color.hpp>
#include <optional>

namespace guim::traits
{
    class background_color
    {
    protected:
        std::optional<color> _bg_color;

    public:
        void set_background_color(const color& col) noexcept;
        void reset_background_color() noexcept;

        color get_background_color() const noexcept;

        void push_background_color();
        void pop_background_color();
    };
}