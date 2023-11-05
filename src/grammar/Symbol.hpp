#ifndef SYMBOL_H
#define SYMBOL_H
#include <memory>
#include <vector>

#include "enumeration.hpp"

class GrammarSymbols;

class Symbol
{
    const SymbolId m_id;

public:
    SymbolId
    id( ) const
    {
        return m_id;
    }

    virtual bool
    is_terminal( ) const
    {
        return false;
    }

    virtual bool
    is_epsilon( ) const
    {
        return false;
    }

    bool
    is_non_terminal( ) const
    {
        return !is_terminal( ) && !is_epsilon( );
    }

    bool
    is_valid( ) const
    {
        return m_id != INVALID_ID;
    }

    bool
    operator==( const Symbol& other ) const
    {
        return m_id == other.m_id;
    }

    virtual ~Symbol( )
    {
    }

protected:
    Symbol( SymbolId id )
        : m_id{ id }
    {
    }
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

using SymbolPtr = std::shared_ptr< const Symbol >;
using Symbols = std::vector< SymbolPtr >;

struct SymbolsHash
{
    std::size_t
    operator( )( const Symbols& symbols ) const
    {
        std::size_t seed = 0;

        // Combine the hashes of individual Symbols
        for ( const auto& symbol : symbols )
        {
            seed ^= std::hash< SymbolPtr >{ }( symbol );
        }

        return seed;
    }
};

#endif  // SYMBOL_H
