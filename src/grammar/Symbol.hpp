#ifndef SYMBOL_H
#define SYMBOL_H
#include <vector>

#include "enumeration.hpp"

struct Symbol
{
    SymbolId id = INVALID_ID;
    bool is_terminal;

    Symbol( bool is_terminal )
        : is_terminal{ true }
    {
    }

    bool
    operator==( const Symbol& other ) const
    {
        return id == other.id && is_terminal == other.is_terminal;
    }
};

using Symbols = std::vector< Symbol >;

#endif  // SYMBOL_H
