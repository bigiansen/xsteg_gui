#pragma once

#include <guim/container.hpp>
#include <string>

namespace guim
{
    class frame : public container
    {
    private:
        std::string _name;

    public:
		bool border_enabled = false;

        frame(const std::string& name, ImVec2 size = ImVec2(0, 0));
        void update() override;
    };
}