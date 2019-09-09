#pragma once

#include <guim/container.hpp>
#include <guim/traits/background_color.hpp>
#include <guim/traits/foreground_color.hpp>
#include <string>

namespace guim
{
    class popup
        : public container
        , public traits::background_color
        , public traits::foreground_color
    {
    protected:
        std::string _name;

    public:

        popup(const std::string& title_label, ImVec2 size = ImVec2(0, 0));
        void show();
        virtual void update() override;
    };
}