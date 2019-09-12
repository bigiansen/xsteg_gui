#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>
#include <string>
#include <unordered_map>

namespace guim
{
    typedef GLuint texture_id_t;

    struct texture_info
    {
        int width = -1, height = -1, channels = -1;
        texture_id_t tex_id = 0;
    };

    class texture_storage
    {
    private:
        std::unordered_map<std::string, texture_info> _tex_dict;
        using iter = decltype(_tex_dict)::iterator;

    public:
        iter emplace_from_file(const std::string& filename);
        bool contains(const std::string& filename);
        texture_id_t get_id(const std::string& filename);
    };

    extern texture_storage global_tex_storage;
    extern texture_id_t get_texture_id(const std::string& filename);
}