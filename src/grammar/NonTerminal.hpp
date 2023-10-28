#ifndef NONTERMINAL_HPP
#define NONTERMINAL_HPP
#include <vector>

#include "Symbol.hpp"
#include "SymbolType.hpp"

enum class NonTerminalType : SymbolId;

struct NonTerminal : public Symbol
{
    NonTerminalType type;

    NonTerminal( );

    NonTerminal( NonTerminalType type );

    bool is_valid( ) const;

    bool operator==( const NonTerminal& other ) const;
};

struct NonTerminalHash
{
    std::size_t
    operator( )( const NonTerminal& non_terminal ) const
    {
        return std::hash< std::size_t >( )( static_cast< std::size_t >( non_terminal.type ) );
    }
};

enum class NonTerminalType : SymbolId
{
    INVALID
};

static const NonTerminal INVALID_NON_TERMINAL = NonTerminal{ NonTerminalType::INVALID };

using NonTerminals = std::vector< NonTerminal >;
#endif  // NONTERMINAL_HPP
