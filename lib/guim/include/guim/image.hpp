#pragma once

#include <guim/texture.hpp>
#include <guim/widget.hpp>
#include <string>

namespace guim 
{
    class image : public widget
    {
    protected:
        std::string _label;
        std::string _id;
        texture_id_t _tex_id = 0;
        bool _needs_ogl_cleanup = false;

    public:
        image(
            const std::string& label,
            ImVec2 sz = ImVec2(0, 0));

        virtual ~image();

        void load_from_file(const std::string& fname);
        void load_from_image(
            const std::string& uid, 
            const uint8_t* data_rgba, 
            int width, 
            int height);

        void update() override;
    };
}