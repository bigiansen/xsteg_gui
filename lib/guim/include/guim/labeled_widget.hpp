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
		template<typename TString, typename = tt::enable_if_stringish<TString>>
		labeled_widget(TString&& label, ImVec2 size = ImVec2(0, 0))
			: widget(size)
		{ 
			if constexpr (tt::is_cstring<TString>)
			{
				_label = std::string(std::forward<TString>(label));
			}
			else
			{
				_label = std::forward<TString>(label);
			}
		}
	};
}