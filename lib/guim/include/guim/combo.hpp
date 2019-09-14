#pragma once

#include <guim/widget.hpp>
#include <vector>
#include <string>
#include <guim/type_traits.hpp>

namespace guim
{
    class combo : public widget
    {
    protected:
        std::vector<std::string> _items;
        std::string _label;
        int* _selected_index;
    
    public:
        template<typename TString, typename = tt::enable_if_string<TString>>
        combo(TString&& label, int* selected_index, ImVec2 size = ImVec2(0, 0))
            : widget(size)
            , _label(std::forward<TString&&>(label))
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

        void update() override;
    };
}