#pragma once

#include <guim/widget.hpp>
#include <guim/traits/foreground_color.hpp>
#include <string>

namespace guim
{
    class text 
        : public widget
        , public traits::foreground_color
    {
    protected:
        std::string _text;

    public:
        text(const std::string& text, ImVec2 size = ImVec2(0, 0));
        virtual void update() override;
    };
}