#pragma once

#include <guim/texture.hpp>
#include <guim/type_traits.hpp>
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
        template<typename TStr, typename = tt::enable_if_stringish<TStr>>
        image(TStr&& label, ImVec2 sz = ImVec2(0, 0))
            : _label(std::forward<TStr>(label))
        { }

        virtual ~image();

        void load_from_file(const std::string& fname);

        void load_from_image(
            const uint8_t* data_rgba, 
            int width, 
            int height);

        void update() override;
    };
}