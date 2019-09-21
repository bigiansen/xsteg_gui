#include <guim/float_slider.hpp>

namespace guim
{
    void float_slider::update()
    {
		if(!enabled) { return; }
        
        if(_size.x > 0)
        {
            ImGui::SetNextItemWidth(_size.x);
        }
        ImGui::SliderFloat(_label.c_str(), &value, _min_value, _max_value);
        if(sameline) { ImGui::SameLine(); }
    }
}
