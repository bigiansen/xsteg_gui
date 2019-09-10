#pragma once

#include <guim/color.hpp>
#include <guim/widget.hpp>
#include <guim/traits/background_color.hpp>
#include <guim/traits/foreground_color.hpp>
#include <string>
#include <optional>

namespace guim
{
	class text_input 
		: public widget
		, public traits::background_color
		, public traits::foreground_color
	{
	protected:
		std::string _label;
		std::string _text;
		bool _readonly = false;

	public:
		text_input(const std::string& label_id, size_t max_size = 255);

		void readonly(bool readonly);
		bool readonly();

		std::string& text();

		void update() override;
	};
}