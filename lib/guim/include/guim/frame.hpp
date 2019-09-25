#pragma once

#include <guim/container.hpp>
#include <guim/type_traits.hpp>
#include <string>

namespace guim
{
    class frame : public container
    {
    private:
        std::string _label;

    public:
		bool border_enabled = false;

        template<typename TStr, typename = tt::enable_if_stringish<TStr>>
        frame(TStr&& label, ImVec2 size = ImVec2(0, 0))
            : container(size)
            , _label(std::forward<TStr>(label))
        { }
        
        void update() override;
    };
}