#include <guim/frame.hpp>

namespace guim
{
    void frame::update()
    {
        ImGui::BeginChild(_label.c_str(), _size, border_enabled);
        container::update();
        ImGui::EndChild();
    }
}