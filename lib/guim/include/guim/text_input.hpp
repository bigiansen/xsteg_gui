#pragma once

#include <guim/color.hpp>
#include <guim/type_traits.hpp>
#include <guim/widget.hpp>
#include <guim/traits/background_color.hpp>
#include <guim/traits/foreground_color.hpp>
#include <functional>
#include <optional>
#include <string>

namespace guim
{
	class text_input : public widget
	{
	protected:
		typedef std::function<void(const std::string&)> text_change_callback_t;
		std::string _label;
		std::string _text;
		text_change_callback_t _edit_callback = nullptr;

	public:
		
		bool readonly = false;
		traits::background_color background_color;
		traits::foreground_color foreground_color;

		text_input(
			const std::string& label_id, 
			size_t max_size = 255, 
			ImVec2 sz = ImVec2(0, 0));

		std::string& text();

		template<typename TStr, typename = tt::enable_if_stringish<TStr>>
		void set_text(TStr&& txt)
		{
			_text = tt::forward_stringish(txt);
		}

		void set_text_change_callback(text_change_callback_t cback) 
		{ _edit_callback = cback; }

		void update() override;
	};
}