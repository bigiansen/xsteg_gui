#include <guim/frame.hpp>

namespace guim
{
    frame::frame(const std::string& name, ImVec2 size)
        : _name(name)
        , container(size)
    { }

    void frame::update()
    {
        ImGui::BeginChild(_name.c_str(), _size, border_enabled);
        container::update();
        ImGui::EndChild();
    }
}