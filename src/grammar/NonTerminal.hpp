#ifndef NONTERMINAL_HPP
#define NONTERMINAL_HPP
#include <vector>

#include "Symbol.hpp"
#include "SymbolType.hpp"

enum class NonTerminalType : SymbolId;

class NonTerminal : public Symbol
{
    const NonTerminalType m_type;

public:
    NonTerminal( );

    NonTerminalType type( ) const;

    bool is_terminal( ) const override;

    bool is_valid( ) const;

    bool operator==( const NonTerminal& other ) const;

    static std::shared_ptr< const NonTerminal > InvalidNonTerminal( );

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
    INVALID,
    A,
    B,
    C,
    D,
    S
};

using NonTerminalPtr = std::shared_ptr< const NonTerminal >;
using NonTerminals = std::vector< NonTerminalPtr >;

#endif  // NONTERMINAL_HPP
