#include <guim/float_slider.hpp>

namespace guim
{
    float float_slider::value()
    {
        return _value;
    }

    void float_slider::update()
    {
        if(enabled)
        {
            if(_size.x > 0)
            {
                ImGui::SetNextItemWidth(_size.x);
            }
            ImGui::SliderFloat(_label.c_str(), &_value, _min_value, _max_value);
            if(sameline) { ImGui::SameLine(); }
        }
    }
}
