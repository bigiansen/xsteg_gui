#pragma once

#include <guim/container.hpp>
#include <guim/type_traits.hpp>
#include <optional>
#include <string>

namespace guim
{
    class window : public container
    {
    protected:
        std::string _label;
        std::optional<ImVec2> _position;
        ImVec2 _current_window_sz;

    public:
        bool background = true;
        bool titlebar = true;
        bool resizable = true;
        bool never_on_front = false;

        template<typename TStr, typename = tt::enable_if_stringish<TStr>>
        window(TStr&& label, ImVec2 size = ImVec2(0, 0))
            : container(size)
            , _label(std::forward<TStr>(label))
        { }
        
        void set_position(ImVec2 pos);
        void reset_position();

        ImVec2 get_current_window_sz();
        
        void update() override;
    };
}