#include <guim/image.hpp>
#include <stdexcept>

namespace guim
{
    image::image(const std::string& label, ImVec2 sz)
        : widget(sz)
        , _label(label)
    { }

    image::~image()
    {
        if(_needs_ogl_cleanup)
        {
            glDeleteTextures(1, &_tex_id);
        }
    }

    void image::load_from_file(const std::string& fname)
    {
        _id = fname;
        _tex_id = get_texture_id(fname);
    }

    void image::load_from_image(
        const std::string& uid, 
        const uint8_t* data_rgba, 
        int width, 
        int height)
    {
        _needs_ogl_cleanup = true;

        glGenTextures(1, &_tex_id);
        glBindTexture(GL_TEXTURE_2D, _tex_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GL_RGBA, 
            width, 
            height, 
            0, 
            GL_RGBA, 
            GL_UNSIGNED_BYTE, 
            data_rgba);
    }

    void image::update()
    {
		if(!enabled) { return; }
        if(_tex_id == 0)
        {
            throw new std::logic_error("Texture id not initialized!");
        }
        
        ImGui::Image((void*)(intptr_t)_tex_id, _size);
        if(sameline) { ImGui::SameLine(); }
    }
}