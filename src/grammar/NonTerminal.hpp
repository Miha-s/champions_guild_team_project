#ifndef NONTERMINAL_HPP
#define NONTERMINAL_HPP
#include <vector>

#include "Symbol.hpp"
#include "SymbolType.hpp"

enum class NonTerminalGroup : SymbolId
{

};

enum class NonTerminalSubgroup : SymbolId
{

};

struct NonTerminal : public Symbol
{
    SymbolType< NonTerminalGroup, NonTerminalSubgroup > type;

    NonTerminal( )
        : Symbol{ false }
    {
    }

    NonTerminal( NonTerminalGroup group, NonTerminalSubgroup subgroup )
        : Symbol{ false }
        , type{ group, subgroup }
    {
    }

    bool
    operator==( const NonTerminal& other ) const
    {
        return type == other.type;
    }
};

using NonTerminals = std::vector< NonTerminal >;
#endif  // NONTERMINAL_HPP
