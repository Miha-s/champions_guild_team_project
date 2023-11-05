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
    StringType
    to_string( ) const override
    {
        return "e";
    }

protected:
    friend class GrammarSymbols;
    Epsilon( )
        : Symbol( EPSILON_ID )
    {
    }
};

using EpsilonPtr = std::shared_ptr< const Epsilon >;

#endif  // EPSILON_HPP
