#ifndef COUNTER_HPP
#define COUNTER_HPP
#include "enumeration.hpp"

struct Counter
{
    SymbolId
    get_next_id( )
    {
        return current_id++;
    }

private:
    SymbolId current_id = 1;
};

#endif  // COUNTER_HPP
