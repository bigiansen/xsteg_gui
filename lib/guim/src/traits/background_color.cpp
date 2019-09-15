#include <guim/traits/background_color.hpp>

namespace guim::traits
{
	void background_color::reset()
	{
		_color.reset();
	}

    void background_color::push()
    {
        if(_color)
        {
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ChildBg, *_color);
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_FrameBg, *_color);
        }
    }

    void background_color::pop()
    {
        if(_color)
        {
            ImGui::PopStyleColor(2);
        }
    }

	color* background_color::operator->()
	{
		return &(*_color);
	}
}