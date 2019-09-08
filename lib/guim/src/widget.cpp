#include <guim/widget.hpp>

namespace guim
{
    widget::widget(ImVec2 size)
        : _size(size)
    { }

    void widget::enable(bool enable) noexcept
    {
        _enabled = enable;
    }

    bool widget::enabled() const noexcept
    { 
        return _enabled;
    }

    void widget::set_size(ImVec2 sz) noexcept
    {
        _size = sz;
    }
}