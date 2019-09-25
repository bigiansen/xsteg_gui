#pragma once

#include <guim/type_traits.hpp>
#include <guim/widget.hpp>
#include <string>

namespace guim
{
	class labeled_widget : public widget
	{
	protected:
		std::string _label;

	public:
		template<typename TStr, typename = tt::enable_if_stringish<TStr>>
		labeled_widget(TStr&& label, ImVec2 size = ImVec2(0, 0))
			: widget(size)
			, _label(std::forward<TStr>(label))
		{ }
	};
}