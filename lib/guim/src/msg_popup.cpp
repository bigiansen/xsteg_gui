#include <guim/msg_popup.hpp>

namespace guim
{
    msg_popup::msg_popup(
        const std::string& label, 
        const std::string& msg,
        ImVec2 size)
        : popup(label, size)
        , _message(msg)
    {
        _text = add_widget<guim::text>(msg, _size);
    }
}