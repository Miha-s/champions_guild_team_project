#ifndef SYMBOL_H
#define SYMBOL_H
#include <vector>

#include "enumeration.hpp"

class GrammarSymbols;

class Symbol
{
    SymbolId m_id = INVALID_ID;
    bool m_is_terminal;

public:
    SymbolId
    id( )
    {
        return m_id;
    }

    bool
    is_terminal( )
    {
        return m_is_terminal;
    }

    bool
    is_valid( ) const
    {
        return m_id != INVALID_ID;
    }

    bool
    operator==( const Symbol& other ) const
    {
        return m_id == other.m_id && m_is_terminal == other.m_is_terminal;
    }

protected:
    Symbol( bool is_terminal, SymbolId id )
        : m_is_terminal{ is_terminal }
        , m_id{ id }
    {
    }

    friend class GrammarSymbols;
};

using Symbols = std::vector< Symbol >;

#endif  // SYMBOL_H
