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
    non_terminals( ) const
    {
        return m_non_terminals;
    }

    const TerminalsSet&
    terminals( ) const
    {
        return m_terminals;
    }

    Terminal
    define( TerminalGroup group, TerminalSubgroup subgroup )
    {
        auto it = std::find_if( m_terminals.cbegin( ),
                                m_terminals.cend( ),
                                [ group, subgroup ]( const Terminal& terminal ) {
                                    return terminal.group( ) == group
                                           && terminal.subgroup( ) == subgroup;
                                } );

        if ( it != m_terminals.cend( ) )
        {
            return *it;
        }

        auto new_symbol = m_terminals.insert( { group, subgroup, m_counter.get_next_id( ) } );
        return *new_symbol.first;
    }

    NonTerminal
    define( NonTerminalType type )
    {
        auto it = std::find_if(
                m_non_terminals.cbegin( ),
                m_non_terminals.cend( ),
                [ type ]( const NonTerminal& non_terminal ) { return non_terminal.m_type == type; } );

        if ( it != m_non_terminals.cend( ) )
        {
            return *it;
        }

        auto new_symbol = m_non_terminals.insert( { type, m_counter.get_next_id( ) } );
        return *new_symbol.first;
    }

    Terminal
    get_terminal( TerminalGroup group, TerminalSubgroup subgroup ) const
    {
        auto it = std::find_if( m_terminals.cbegin( ),
                                m_terminals.cend( ),
                                [ group, subgroup ]( const Terminal& terminal ) {
                                    return terminal.group( ) == group
                                           && terminal.subgroup( ) == subgroup;
                                } );

        if ( it != m_terminals.cend( ) )
        {
            return *it;
        }

        return Terminal::INVALID_TERMINAL;
    }

    NonTerminal
    get_non_terminal( NonTerminalType type ) const
    {
        auto it = std::find_if(
                m_non_terminals.cbegin( ),
                m_non_terminals.cend( ),
                [ type ]( const NonTerminal& non_terminal ) { return non_terminal.m_type == type; } );

        if ( it != m_non_terminals.cend( ) )
        {
            return *it;
        }

        return NonTerminal::INVALID_NON_TERMINAL;
    }
};

#endif  // GRAMMARSYMBOLS_HPP
