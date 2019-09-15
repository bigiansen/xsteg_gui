#include <guim/image.hpp>

namespace guim
{
    image::image(const std::string& label, const std::string& img_fname, ImVec2 sz)
        : widget(sz)
        , _label(label)
        , _img_fname(img_fname)
    { }

    void image::update()
    {
		if(!enabled) { return; }
        
        texture_id_t tex_id = get_texture_id(_img_fname);
        ImGui::Image((void*)(intptr_t)tex_id, _size);
        if(sameline) { ImGui::SameLine(); }        
    }
}