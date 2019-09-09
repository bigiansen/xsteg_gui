#include <guim/widget.hpp>

namespace guim
{
    widget::widget(ImVec2 size)
        : _size(size)
    { }
    
    void widget::set_size(ImVec2 sz) noexcept
    {
        _size = sz;
    }
}