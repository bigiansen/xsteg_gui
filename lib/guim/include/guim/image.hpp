#pragma once

#include <guim/texture.hpp>
#include <guim/widget.hpp>
#include <string>

namespace guim 
{
    class image : public widget
    {
    protected:
        std::string _label, _img_fname;

    public:
        image(
            const std::string& label, 
            const std::string& img_fname, 
            ImVec2 sz = ImVec2(0, 0));

        void update() override;
    };
}