#include <guim/text_input.hpp>

#include <imgui.h>
#include <imgui_stdlib.h>

namespace guim
{
	text_input::text_input(const std::string& label_id, size_t max_size, ImVec2 sz)
		: widget(sz)
		, _label(label_id)
		, _text(max_size, '\0')
	{ }

	std::string& text_input::text()
	{
		return _text;
	}

	void text_input::update()
	{		
		if(!enabled) { return; }
		
		background_color.push();
        foreground_color.push();

		ImGuiInputTextFlags flags = 0;
		if(readonly)
		{
			flags |= ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly;
		}
		if(_size.x > 0)
		{
			ImGui::SetNextItemWidth(_size.x);
		}
		ImGui::InputText(_label.c_str(), _text.data(), _text.length() + 1, flags, _edit_callback);

		background_color.pop();
        foreground_color.pop();
			
		if(sameline)
		{
			ImGui::SameLine();
		}		
	}
}