#pragma once

#include <guim/labeled_widget.hpp>
#include <guim/type_traits.hpp>
#include <vector>
#include <string>

namespace guim
{
    class combo : public labeled_widget
    {
    protected:
        std::vector<std::string> _items;
        int _selected_index = 0;
    
    public:
        template<typename TString, typename = tt::enable_if_stringish<TString>>
        combo(TString&& label, int selected_index = 0, ImVec2 size = ImVec2(0, 0))
            : labeled_widget(std::forward<TString>(label), size)
            , _selected_index(selected_index)
        { }

        template<typename TString, typename = tt::enable_if_string<TString>>
        int add_item(TString&& item)
        {
            _items.push_back(std::forward(item));
            return (int)_items.size();
        }

        template<typename TContainer, typename = std::enable_if_t<tt::is_iterable_of<TContainer, std::string>>>
        int add_items(TContainer&& cont)
        {            
            if constexpr(std::is_rvalue_reference_v<TContainer>)
            {
                std::move(cont.begin(), cont.end(), std::back_inserter(_items));
            }
            else
            {
                std::copy(cont.begin(), cont.end(), std::back_inserter(_items));
            }                  
            return (int)_items.size();
        }

		int selected_index();

        void update() override;
    };
}