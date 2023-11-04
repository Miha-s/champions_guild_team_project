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
#include "Epsilon.hpp"

class GrammarSymbols
{
    Counter m_counter;
    using NonTerminalsSet = std::unordered_set< NonTerminalPtr >;
    using TerminalsSet = std::unordered_set< TerminalPtr >;
    NonTerminalsSet m_non_terminals;
    TerminalsSet m_terminals;
    std::shared_ptr< const Epsilon > m_epsilon;

public:
    GrammarSymbols( )
        : m_epsilon{ new Epsilon{} }
    {
    }

    std::shared_ptr< const Epsilon >
    epsilon( )
    {
        return m_epsilon;
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

    TerminalPtr
    define( TerminalGroup group, TerminalSubgroup subgroup )
    {
        auto it = std::find_if( m_terminals.cbegin( ),
                                m_terminals.cend( ),
                                [ group, subgroup ]( const TerminalPtr& terminal ) {
                                    return terminal->group( ) == group
                                           && terminal->subgroup( ) == subgroup;
                                } );

        if ( it != m_terminals.cend( ) )
        {
            return *it;
        }

        auto new_symbol = m_terminals.insert(
                TerminalPtr{ new Terminal{ group, subgroup, m_counter.get_next_id( ) } } );
        return *new_symbol.first;
    }

    NonTerminalPtr
    define( NonTerminalType type )
    {
        auto it = std::find_if( m_non_terminals.cbegin( ),
                                m_non_terminals.cend( ),
                                [ type ]( const NonTerminalPtr& non_terminal ) {
                                    return non_terminal->m_type == type;
                                } );

        if ( it != m_non_terminals.cend( ) )
        {
            return *it;
        }

        auto new_symbol = m_non_terminals.insert(
                NonTerminalPtr{ new NonTerminal{ type, m_counter.get_next_id( ) } } );
        return *new_symbol.first;
    }

    TerminalPtr
    get_terminal( TerminalGroup group, TerminalSubgroup subgroup ) const
    {
        auto it = std::find_if( m_terminals.cbegin( ),
                                m_terminals.cend( ),
                                [ group, subgroup ]( const TerminalPtr& terminal ) {
                                    return terminal->group( ) == group
                                           && terminal->subgroup( ) == subgroup;
                                } );

        if ( it != m_terminals.cend( ) )
        {
            return *it;
        }

        return Terminal::InvalidTerminal( );
    }

    NonTerminalPtr
    get_non_terminal( NonTerminalType type ) const
    {
        auto it = std::find_if( m_non_terminals.cbegin( ),
                                m_non_terminals.cend( ),
                                [ type ]( const NonTerminalPtr& non_terminal ) {
                                    return non_terminal->m_type == type;
                                } );

        if ( it != m_non_terminals.cend( ) )
        {
            return *it;
        }

        return NonTerminal::InvalidNonTerminal( );
    }
};

#endif  // GRAMMARSYMBOLS_HPP
