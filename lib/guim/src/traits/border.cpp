#include <guim/traits/border.hpp>

namespace guim::traits
{
    void border::enable_border(bool enable)
    {
        _border_enabled = enable;
    }

    bool border::border_enabled()
    {
        return _border_enabled;
    }
}