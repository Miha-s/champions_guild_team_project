#ifndef SYMBOL_H
#define SYMBOL_H

#include "enumeration.hpp"

struct Symbol
{
    SymbolId id;
    virtual bool is_terminal( ) const = 0;
};

#endif // SYMBOL_H
