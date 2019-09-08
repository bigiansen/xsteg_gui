#pragma once

namespace guim::traits
{
    class border
    {
    protected:
        bool _border_enabled = false;
    
    public:
        void enable_border(bool enable);
        bool border_enabled();
    };
}