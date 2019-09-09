#pragma once

#include <guim/color.hpp>
#include <optional>

namespace guim::traits
{
    struct foreground_color
    {
        std::optional<color> color_foreground;

        void push();
        void pop();
    };
}