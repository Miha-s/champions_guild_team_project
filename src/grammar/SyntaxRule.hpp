#ifndef SYNTAXRULE_H
#define SYNTAXRULE_H

#include <vector>

#include "Countable.hpp"
#include "NonTerminal.hpp"

class SyntaxRule
{
public:
    template < typename... Symbols >
    SyntaxRule( SymbolId id, NonTerminal left_side, const Symbols&... right_side )
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
        return m_id != INVALID_ID && m_left_side.is_valid( );
    }

    NonTerminal
    get_left_side( ) const
    {
        return this->m_left_side;
    }

    Symbols
    get_right_side( ) const
    {
        return this->m_right_side;
    }

private:
    SymbolId m_id;
    NonTerminal m_left_side;
    Symbols m_right_side;
};

static const SyntaxRule INVALID_RULE = SyntaxRule{ INVALID_ID, NonTerminal::INVALID_NON_TERMINAL };

#endif  // SYNTAXRULE_H
