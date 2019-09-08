#pragma once

#include <guim/container.hpp>
#include <string>

namespace guim
{
    class window : public container
    {
    private:
        std::string _name;

    public:
        window(const std::string& name, ImVec2 size = ImVec2(0, 0));
    };
}