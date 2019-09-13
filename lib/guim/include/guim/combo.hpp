#pragma once

#include <guim/widget.hpp>
#include <vector>
#include <string>
#include <type_traits>

namespace guim
{
    class combo : public widget
    {
    private:
        template<typename TStr>
        using enable_if_string = std::enable_if_t<std::is_same_v<std::decay_t<TStr>, std::string>>;

        template<typename, typename = std::void_t<>>
        struct is_iterable : std::false_type { };

        template<typename TContainer>
        struct is_iterable<TContainer, std::void_t<
            decltype(std::declval<TContainer>().begin()),
            decltype(std::declval<TContainer>().end())>> : std::true_type { };

        template<typename, typename = std::void_t<>>
        struct is_string_container : std::false_type { };

        template<typename TContainer>
        struct is_string_container<TContainer, std::enable_if_t<
            std::is_same_v<std::string, std::decay_t<decltype(*(std::declval<TContainer>().begin()))>>
        >> : std::true_type { };

    protected:
        std::vector<std::string> _items;
        std::string _label;
        int* _selected_index;
    
    public:
        template<typename TString, typename = enable_if_string<TString>>
        combo(TString&& label, int* selected_index, ImVec2 size = ImVec2(0, 0))
            : widget(size)
            , _label(std::forward<TString&&>(label))
            , _selected_index(selected_index)
        { }

        template<typename TString, typename = enable_if_string<TString>>
        int add_item(TString&& item)
        {
            _items.push_back(std::forward(item));
            return (int)_items.size();
        }

        template<typename TContainer, 
            typename = std::enable_if_t<is_iterable<TContainer>() && is_string_container<TContainer>()>>
        int add_items(TContainer&& cont)
        {
            std::copy(cont.begin(), cont.end(), std::back_inserter(_items));
            return (int)_items.size();
        }

        void update() override;
    };
}