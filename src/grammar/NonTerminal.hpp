#ifndef NONTERMINAL_HPP
#define NONTERMINAL_HPP
#include <vector>

#include "Symbol.hpp"
#include "SymbolType.hpp"

enum class NonTerminalType : SymbolId;

class NonTerminal : public Symbol
{
    NonTerminalType m_type;

public:
    NonTerminal( );

    NonTerminalType type( ) const;

    bool is_valid( ) const;

    bool operator==( const NonTerminal& other ) const;

    static const NonTerminal INVALID_NON_TERMINAL;

protected:
    NonTerminal( NonTerminalType type, SymbolId id );

    friend class GrammarSymbols;
};

struct NonTerminalHash
{
    std::size_t
    operator( )( const NonTerminal& non_terminal ) const
    {
        return std::hash< std::size_t >( )( static_cast< std::size_t >( non_terminal.type( ) ) );
    }
};

enum class NonTerminalType : SymbolId
{
    INVALID
};

using NonTerminals = std::vector< NonTerminal >;
#endif  // NONTERMINAL_HPP
