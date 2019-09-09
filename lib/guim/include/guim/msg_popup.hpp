#pragma once

#include <guim/popup.hpp>
#include <guim/text.hpp>
#include <string>

namespace guim
{
    class msg_popup : public popup
    {
    protected:
        std::string _message;
        guim::text* _text;
    public:
        msg_popup(
            const std::string& label,
            const std::string& msg,
            ImVec2 size = ImVec2(0, 0));
    };
}