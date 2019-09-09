#include <guim/container.hpp>

namespace guim
{
    container::container(ImVec2 size)
        : widget(size)
    { }

    void container::clear_widgets()
    {
        _widgets.clear();
    }

    void container::update()
    {
        if(enabled)
        {
            size_t count = _widgets.size();
            for(size_t i = 0; i < count; ++i)
            {
                _widgets[i]->update();
            }
        }
    }
}