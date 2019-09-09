#include <guim/container.hpp>

namespace guim
{
    container::container(ImVec2 size)
        : widget(size)
    { }

    void container::update()
    {
        if(enabled)
        {
            for(auto& widget : _widgets)
            {
                widget->update();
            }
        }
    }
}