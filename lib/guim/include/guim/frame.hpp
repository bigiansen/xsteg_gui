#pragma once

#include <guim/container.hpp>
#include <guim/traits/border.hpp>
#include <string>

namespace guim
{
    class frame 
        : public container
        , public traits::border
    {
    private:
        std::string _name;

    public:
        frame(const std::string& name, ImVec2 size = ImVec2(0, 0));
        void update() override;
    };
}