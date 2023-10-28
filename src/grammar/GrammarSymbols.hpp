#ifndef GRAMMARSYMBOLS_HPP
#define GRAMMARSYMBOLS_HPP

#include <algorithm>
#include <memory>
#include <unordered_set>
#include <vector>

#include "Countable.hpp"
#include "Counter.hpp"
#include "NonTerminal.hpp"
#include "Terminal.hpp"

class GrammarSymbols
{
    Counter m_counter;
    using NonTerminalsSet = std::unordered_set< NonTerminal, NonTerminalHash >;
    using TerminalsSet = std::unordered_set< Terminal, TerminalHash >;
    NonTerminalsSet m_non_terminals;
    TerminalsSet m_terminals;

public:
    GrammarSymbols( )
    {
    }

    const NonTerminalsSet&
    non_terminals( )
    {
        return m_non_terminals;
    }

    const TerminalsSet&
    terminals( )
    {
        return m_terminals;
    }

    Terminal
    get_terminal( TerminalGroup group, TerminalSubgroup subgroup ) const
    {
        auto it = std::find( m_terminals.cbegin( ),
                             m_terminals.cend( ),
                             Terminal{ group, subgroup } );
        if ( it != m_terminals.cend( ) )
        {
            return *it;
        }

        return INVALID_TERMINAL;
    }

    NonTerminal
    get_non_terminal( NonTerminalType type ) const
    {
        auto it = std::find( m_non_terminals.cbegin( ),
                             m_non_terminals.cend( ),
                             NonTerminal{ type } );

        if ( it != m_non_terminals.cend( ) )
        {
            return *it;
        }

        return INVALID_NON_TERMINAL;
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
            m_non_terminals.insert( symbol );
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

        if ( it == m_terminals.end( ) )
        {
            symbol.id = m_counter.get_next_id( );
            m_terminals.insert( symbol );
        }
        else
        {
            symbol.id = it->id;
        }
    }
};

#endif  // GRAMMARSYMBOLS_HPP
