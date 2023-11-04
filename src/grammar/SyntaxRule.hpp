#ifndef SYNTAXRULE_H
#define SYNTAXRULE_H

#include <vector>

#include "Countable.hpp"
#include "NonTerminal.hpp"

class SyntaxRule
{
public:
    template < typename... SymbolsT >
    SyntaxRule( SymbolId id, NonTerminalPtr left_side, const SymbolsT&... right_side )
        : m_id{ id }
        , m_left_side{ left_side }
        , m_right_side{ right_side... }
    {
    }

    SymbolId
    id( ) const
    {
        return m_id;
    }

    bool
    is_valid( ) const
    {
        return m_id != INVALID_ID && m_left_side->is_valid( );
    }

    NonTerminalPtr
    get_left_side( ) const
    {
        return this->m_left_side;
    }

    Symbols
    get_right_side( ) const
    {
        return m_right_side;
    }

    bool
    contains( const SymbolPtr& symbol ) const
    {
        for ( const auto& item : m_right_side )
        {
            if ( item == symbol )
            {
                return true;
            }
        }
        return false;
    }

    static std::shared_ptr< const SyntaxRule >
    InvalidRule( )
    {
        static std::shared_ptr< const SyntaxRule > invalid_rule(
                new SyntaxRule( INVALID_ID, NonTerminal::InvalidNonTerminal( ) ) );
        return invalid_rule;
    }

private:
    SymbolId m_id = INVALID_ID;
    NonTerminalPtr m_left_side;
    Symbols m_right_side;
};

using SyntaxRulePtr = std::shared_ptr< const SyntaxRule >;
using SyntaxRules = std::vector< SyntaxRulePtr >;

#endif  // SYNTAXRULE_H
