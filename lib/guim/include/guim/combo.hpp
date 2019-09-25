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
    
    public:
        int selected_index = 0;

        template<typename TStr, typename = tt::enable_if_stringish<TStr>>
        combo(TStr&& label, int selected_index = 0, ImVec2 size = ImVec2(0, 0))
            : labeled_widget(std::forward<TStr>(label), size)
            , selected_index(selected_index)
        { }

        template<typename TStr, typename = tt::enable_if_string<TStr>>
        int add_item(TStr&& item)
        {
            _items.push_back(std::forward<TStr>(item));
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

        void update() override;
    };
}