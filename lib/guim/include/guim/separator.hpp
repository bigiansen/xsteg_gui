#pragma once

#include <guim/widget.hpp>

namespace guim
{
    class separator : public widget
    {
    public:
        separator();
        void update() override;
    };
}