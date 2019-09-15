#include <guim/traits/foreground_color.hpp>

namespace guim::traits
{
	void foreground_color::reset()
	{
		_color.reset();
	}

    void foreground_color::push()
    {
        if(_color)
        {
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Text, *_color);
        }
    }

    void foreground_color::pop()
    {
        if(_color)
        {
            ImGui::PopStyleColor(1);
        }
    }

	color* foreground_color::operator->()
	{
		return &(*_color);
	}
}