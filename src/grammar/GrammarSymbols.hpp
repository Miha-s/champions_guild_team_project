#ifndef GRAMMARSYMBOLS_HPP
#define GRAMMARSYMBOLS_HPP

#include <algorithm>
#include <memory>
#include <vector>

#include "Countable.hpp"
#include "Counter.hpp"
#include "NonTerminal.hpp"
#include "Terminal.hpp"

class GrammarSymbols
{
    Counter m_counter;
    std::vector< NonTerminal > m_non_terminals;
    std::vector< Terminal > m_terminals;

public:
    GrammarSymbols( )
    {
    }

    const std::vector< NonTerminal >&
    non_terminals( )
    {
        return m_non_terminals;
    }

    const std::vector< Terminal >&
    terminals( )
    {
        return m_terminals;
    }

    template < class... Symbols >
    void
    add_symbol( NonTerminal& symbol, Symbols&... symbols )
    {
        add_symbol( symbol );
        add_symbol( symbols... );
    }

    template < class... Symbols >
    void
    add_symbol( Terminal& symbol, Symbols&... symbols )
    {
        add_symbol( symbol );
        add_symbol( symbols... );
    }

    void
    add_symbol( NonTerminal& symbol )
    {
        auto it = std::find_if( m_non_terminals.begin( ),
                                m_non_terminals.end( ),
                                [ &symbol ]( const NonTerminal& sym ) { return sym == symbol; } );

        if ( it == m_non_terminals.end( ) )
        {
            symbol.id = m_counter.get_next_id( );
            m_non_terminals.push_back( symbol );
        }
        else
        {
            symbol.id = it->id;
        }
    }

    void
    add_symbol( Terminal& symbol )
    {
        auto it = std::find_if( m_terminals.begin( ),
                                m_terminals.end( ),
                                [ &symbol ]( const Terminal& sym ) { return sym == symbol; } );

        if ( it != m_terminals.end( ) )
        {
            symbol.id = m_counter.get_next_id( );
            m_terminals.push_back( symbol );
        }
        else
        {
            symbol.id = it->id;
        }
    }
};

#endif  // GRAMMARSYMBOLS_HPP
