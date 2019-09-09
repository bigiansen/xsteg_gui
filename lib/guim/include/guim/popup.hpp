#pragma once

#include <guim/widget.hpp>
#include <guim/traits/background_color.hpp>
#include <guim/traits/foreground_color.hpp>

namespace guim
{
    class popup
        : public widget
        , public traits::background_color
        , public traits::foreground_color
    {
        
    }
}