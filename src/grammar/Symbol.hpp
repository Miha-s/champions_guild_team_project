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
    id( ) const
    {
        return m_id;
    }

    bool
    is_terminal( ) const
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


            protected : Symbol( bool is_terminal, SymbolId id )
        : m_is_terminal{ is_terminal }
        , m_id{ id }
    {
    }

    friend class GrammarSymbols;
};

struct SymbolHash
{
    std::size_t
    operator( )( const Symbol& symbol ) const
    {
        return std::hash< std::size_t >( )( static_cast< std::size_t >( symbol.is_terminal( ) )
                                            ^ static_cast< std::size_t >( symbol.id( ) ) );
    }
};

using Symbols = std::vector< Symbol >;

struct SymbolsHash
{
    std::size_t
    operator( )( const std::vector< Symbol >& symbols ) const
    {
        std::size_t seed = 0;

        // Combine the hashes of individual Symbols
        for ( const Symbol& symbol : symbols )
        {
            seed ^= SymbolHash{ }( symbol );
        }

        return seed;
    }
};

#endif  // SYMBOL_H
