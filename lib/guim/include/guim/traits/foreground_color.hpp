#pragma once

#include <guim/color.hpp>
#include <guim/type_traits.hpp>
#include <optional>
#include <utility>

namespace guim::traits
{
	class foreground_color
	{
	private:
		std::optional<color> _color;

	public:
		void reset();
		void push();
		void pop();

		template<typename TColor, typename = tt::enable_if_is_type<TColor, color>>
		void operator=(TColor&& col)
		{
			_color = std::forward<TColor>(col);
		}

		color* operator->();
	};
}