#include <guim/texture.hpp>

#include <stdexcept>

namespace guim
{
    texture_storage global_tex_storage;

    texture_storage::iter texture_storage::emplace_from_file(const std::string& filename)
    {
        int w, h, ch;
        uint8_t* data = stbi_load(filename.c_str(), &w, &h, &ch, 4);

        if(data == nullptr)
        {
            throw std::invalid_argument("Could not load image: " + filename);
        }

        emplace_from_image(filename, data, w, h);
        stbi_image_free(data);
    }

    texture_storage::iter texture_storage::emplace_from_image(
        const std::string& id,
        uint8_t* data_rgba, 
        int width, 
        int height)
    {
        texture_info info;
        info.width = width;
        info.height = height;
        info.channels = 4;

        if(data_rgba == nullptr)
        {
            throw std::invalid_argument("Invalid NULL data pointer");
        }

        glGenTextures(1, &info.tex_id);
        glBindTexture(GL_TEXTURE_2D, info.tex_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GL_RGBA, 
            info.width, 
            info.height, 
            0, 
            GL_RGBA, 
            GL_UNSIGNED_BYTE, 
            data_rgba);
        
        auto [iter, ok] = _tex_dict.emplace(id, info);
        return iter;
    }

    bool texture_storage::contains(const std::string& filename)
    {
        return static_cast<bool>(_tex_dict.count(filename));
    }

    texture_id_t texture_storage::get_id(const std::string& filename)
    {
        return _tex_dict[filename].tex_id;
    }

    void texture_storage::erase(const std::string& filename)
    {
        const texture_id_t id = get_texture_id(filename);
        glDeleteTextures(1, &id);
        _tex_dict.erase(filename);
    }

    texture_id_t get_texture_id(const std::string& filename)
    {
        if(global_tex_storage.contains(filename))
        {
            return global_tex_storage.get_id(filename);
        }
        auto [name, info] = *(global_tex_storage.emplace_from_file(filename));
        return info.tex_id;
    }
    
}