#pragma once

#include <guim/container.hpp>
#include <guim/text_input.hpp>
#include <guim/type_traits.hpp>
#include <guim/traits/background_color.hpp>
#include <guim/traits/foreground_color.hpp>
#include <xsteg/availability_map.hpp>

class restore_key_popup : public guim::container
{
private:
    using threshold_container_t = std::vector<xsteg::availability_threshold>;
    std::string _label;
    guim::text_input* _input;
    guim::traits::background_color background_color;
    guim::traits::foreground_color foreground_color;
    threshold_container_t& _thresholds;

public:
    template<typename TStr, typename = guim::tt::enable_if_stringish<TStr>>
    restore_key_popup(
        TStr&& label, 
        threshold_container_t& target, 
        ImVec2 sz = ImVec2(0, 0))
        : container(sz)
        , _label(guim::tt::forward_stringish(label))
        , _thresholds(target)
    {
        init_widgets();
    }

    void update() override;
    void show();

private:
    void init_widgets();
};