#ifndef EPSILON_HPP
#define EPSILON_HPP

#include "Symbol.hpp"

class Epsilon : public Symbol
{
public:
    bool
    is_epsilon( ) const override
    {
        return true;
    }
protected:
    friend class GrammarSymbols;
    Epsilon( )
        : Symbol( EPSILON_ID )
    {
    }
};

#endif  // EPSILON_HPP
