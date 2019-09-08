#include <guim/text_input.hpp>

#include <imgui.h>
#include <imgui_stdlib.h>

namespace guim
{
	text_input::text_input(const std::string& label_id, size_t max_size)
		: _label(label_id)
		, _text(max_size, '\0')
	{ }

	void text_input::update()
	{		
		if (_enabled)
		{
			push_background_color();
			push_foreground_color();

			ImGuiInputTextFlags flags;
			if(_readonly)
			{
				flags |= ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly;
			}

			if(_size.x > 0)
			{
				ImGui::SetNextItemWidth(_size.x);
			}

			ImGui::InputText(_label.c_str(), &_text, flags);

			pop_foreground_color();
			pop_background_color();
		}
	}
}