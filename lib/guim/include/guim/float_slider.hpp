#pragma once

#include <guim/labeled_widget.hpp>
#include <guim/type_traits.hpp>
#include <string>

namespace guim
{
    class float_slider : public labeled_widget
    {
    protected:
        float _min_value;
        float _max_value;
    
    public:
        float value;

        template<typename TStr, typename = tt::enable_if_stringish<TStr>>
        float_slider(
            TStr&& label, 
            float min, 
            float max, 
            float init_value = 0.0F, 
            ImVec2 size = ImVec2(0, 0))
            : labeled_widget(std::forward<TStr>(label), size)
            , _min_value(min)
            , _max_value(max)
            , value(init_value)
        { }

        void update() override;
    };
}