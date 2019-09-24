#pragma once

#include <guim/container.hpp>
#include <guim/traits/background_color.hpp>
#include <guim/traits/foreground_color.hpp>
#include <string>

namespace guim
{
    class popup : public container
    {
    protected:
        std::string _name;

    public:
		traits::background_color background_color;
		traits::foreground_color foreground_color;

        popup(const std::string& title_label, ImVec2 size = ImVec2(0, 0));
        virtual void show();
        virtual void update() override;
    };
}