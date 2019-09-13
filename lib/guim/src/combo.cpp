#include <guim/combo.hpp>

namespace guim
{
    void combo::update()
    {
        if(enabled)   
        {
            if(_size.x > 0)            
            {
                ImGui::SetNextItemWidth(128);
            }
            ImGui::Combo(
                _label.c_str(), 
                _selected_index, 
                [](void* data, int idx, const char** out_text)
                {
                    auto* ptr = reinterpret_cast<const std::vector<std::string>*>(data);
                    *out_text = ptr->at(idx).c_str();
                    return true;
                },
                (void*)&_items,
                (int)_items.size()
            );
        }
    }
}