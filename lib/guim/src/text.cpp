#include <guim/text.hpp>

namespace guim
{
    text::text(const std::string& text, ImVec2 size)
        : widget(size)
        , _text(text)
    { }

    void text::update()
    {
		if(!enabled) { return; }
        
        foreground_color.push();
        ImGui::SetNextItemWidth(_size.x);
        ImGui::Text(_text.c_str());
        foreground_color.pop();
        if(sameline)
        {
            ImGui::SameLine();
        }        
    }
}