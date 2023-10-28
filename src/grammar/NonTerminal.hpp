#ifndef NONTERMINAL_HPP
#define NONTERMINAL_HPP
#include <vector>

#include "Symbol.hpp"
#include "SymbolType.hpp"

enum class NonTerminalGroup : SymbolId;

enum class NonTerminalSubgroup : SymbolId;

struct NonTerminal : public Symbol
{
    SymbolType< NonTerminalGroup, NonTerminalSubgroup > type;

    NonTerminal( );

    NonTerminal( NonTerminalGroup group, NonTerminalSubgroup subgroup );

    bool is_valid( ) const;

    bool operator==( const NonTerminal& other ) const;
};

struct NonTerminalHash
{
    std::size_t
    operator( )( const NonTerminal& non_terminal ) const
    {
        return std::hash< std::size_t >( )(
                static_cast< std::size_t >( non_terminal.type.group )
                ^ static_cast< std::size_t >( non_terminal.type.sub_group ) );
    }
};

enum class NonTerminalGroup : SymbolId
{
    INVALID
};

enum class NonTerminalSubgroup : SymbolId
{
    INVALID
};

static const NonTerminal INVALID_NON_TERMINAL =
        NonTerminal{ NonTerminalGroup::INVALID, NonTerminalSubgroup::INVALID };

using NonTerminals = std::vector< NonTerminal >;
#endif  // NONTERMINAL_HPP
