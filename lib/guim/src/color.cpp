#include <guim/color.hpp>

namespace guim
{
    color::operator ImVec4() const
    {
        return ImVec4(r, g, b, a);
    }
}