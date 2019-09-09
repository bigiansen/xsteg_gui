#pragma once

#include <guim/color.hpp>
#include <optional>

namespace guim::traits
{
    struct background_color
    {
        std::optional<color> color_background;

        void push();
        void pop();
    };
}