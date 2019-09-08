#pragma once

#include <memory>
#include <type_traits>
#include <vector>
#include <guim/widget.hpp>

namespace guim
{
    class container : public widget
    {
    protected:
        std::vector<std::unique_ptr<widget>> _widgets;
    
    public:  
        container(ImVec2 size = ImVec2(0, 0));

        template<typename TWidget, typename... TArgs, typename = std::enable_if_t<std::is_base_of_v<widget, TWidget>>>        
        TWidget* add_widget(TArgs... args)
        {
            auto& ref = _widgets.emplace_back(std::make_unique<TWidget>(args...));
            return ref.get();
        }

        virtual void update() override;
    };
}