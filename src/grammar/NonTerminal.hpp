#ifndef NONTERMINAL_HPP
#define NONTERMINAL_HPP
#include <vector>
#include <unordered_map>

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

    StringType to_string( ) const override;

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

#define EXPAND_VALUES_NON_TERINAL_TYPE(action) \
    action(INVALID) \
    action(A) \
    action(B) \
    action(C) \
    action(D) \
    action(S)

enum class NonTerminalType : SymbolId
{
    EXPAND_VALUES_NON_TERINAL_TYPE(EXPAND_ENUM)
};

using NonTerminalPtr = std::shared_ptr< const NonTerminal >;
using NonTerminals = std::vector< NonTerminalPtr >;

std::ostream& operator<<( std::ostream& os, const NonTerminalPtr& non_temrinal );

#endif  // NONTERMINAL_HPP
