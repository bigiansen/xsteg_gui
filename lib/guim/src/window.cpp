#include <guim/window.hpp>

namespace guim
{
    window::window(const std::string& name, ImVec2 size = ImVec2(0, 0))
        : _name(name)
        , container(size)
    { }
}