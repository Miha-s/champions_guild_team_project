#ifndef COUNTABLE_HPP
#define COUNTABLE_HPP
#include "enumeration.hpp"

template < typename Type >
struct Countable
{
    Type symbol;
    SymbolId id;
};

#endif  // COUNTABLE_HPP
