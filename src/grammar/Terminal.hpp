#ifndef TERMINAL_HPP
#define TERMINAL_HPP
#include <vector>
#include "Symbol.hpp"
#include "SymbolType.hpp"

enum class TerminalGroup : SymbolId
{

};

enum class TerminalSubgroup : SymbolId
{

};

struct Terminal : public Symbol
{
    SymbolType< TerminalGroup, TerminalSubgroup > type;
    StringType word;

    Terminal( )
        : Symbol{ true }
    {
    }

    Terminal( TerminalGroup group, TerminalSubgroup subgroup, StringType word )
        : Symbol{ true }
        , type{ group, subgroup }
        , word{ std::move( word ) }
    {
    }

    bool
    operator==( const Terminal& other ) const
    {
        return type == other.type;
    }
};

using Terminals = std::vector< Terminal >;

#endif  // TERMINAL_HPP
