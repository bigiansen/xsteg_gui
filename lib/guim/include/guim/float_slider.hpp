#pragma once

#include <guim/labeled_widget.hpp>
#include <guim/type_traits.hpp>
#include <string>

namespace guim
{
    class float_slider : public labeled_widget
    {
    protected:
        float _value;
        float _min_value;
        float _max_value;
    
    public:
        template<typename TString, typename = tt::enable_if_stringish<TString>>
        float_slider(TString&& label, float min, float max, float init_value = 0.0F, ImVec2 size = ImVec2(0, 0))
            : labeled_widget(label, size)
            , _min_value(min)
            , _max_value(max)
            , _value(init_value)
        { }

        float value();

        void update() override;        
    };
}