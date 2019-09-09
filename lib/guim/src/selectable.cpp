#include <guim/selectable.hpp>

namespace guim
{
    selectable::selectable(const std::string& label)
        : widget(ImVec2(0, 0))
        , _label(label)
    { }

    void selectable::update()
    {
        if(enabled)
        {
            background_color::push();
            foreground_color::push();

            ImGuiSelectableFlags flags = 0;
            flags |= ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups;
            bool enabled = true;
            if(ImGui::Selectable(_label.c_str(), &enabled, flags))
            {
                for(auto& cback : _callbacks)
                {
                    cback();
                }
            }

            background_color::pop();
            foreground_color::pop();
        }
    }

    void selectable::operator+=(std::function<void()> cback)
    {
        _callbacks.push_back(cback);
    }

    void selectable::add_callback(std::function<void()> cback)
    {
        *this += cback;
    }
}