#ifndef GRAMMAR_HPP
#define GRAMMAR_HPP

#include <utility>
#include <vector>

#include "GrammarSymbols.hpp"
#include "SyntaxRule.hpp"
#include "Terminal.hpp"

class Grammar
{
public:
    Grammar( )
    {
    }

    Terminal
    define( TerminalGroup group, TerminalSubgroup subgroup )
    {
        return m_grammar_symbols.define( group, subgroup );
    }

    NonTerminal
    define( NonTerminalType type )
    {
        return m_grammar_symbols.define( type );
    }

    Terminal
    create( TerminalGroup group, TerminalSubgroup subgroup ) const
    {
        return m_grammar_symbols.get_terminal( group, subgroup );
    }

    NonTerminal
    create( NonTerminalType type ) const
    {
        return m_grammar_symbols.get_non_terminal( type );
    }

    template < class... Symbols >
    void
    add_rule( const Symbols&... symbols )
    {
        m_grammar_rules.push_back( SyntaxRule{ m_rules_counter.get_next_id( ), symbols... } );
    }

    SyntaxRule
    get_rule( SymbolId id )
    {
        auto it = std::find_if( m_grammar_rules.begin( ),
                                m_grammar_rules.end( ),
                                [ id ]( const SyntaxRule& rule ) { return rule.id( ) == id; } );

        return it == m_grammar_rules.end( ) ? INVALID_RULE : *it;
    }

    std::unordered_set< NonTerminal, NonTerminalHash >
    get_non_terminals( ) const
    {
        return this->m_grammar_symbols.non_terminals( );
    }

    std::vector< SyntaxRule >
    get_grammar_rules( ) const
    {
        return this->m_grammar_rules;
    }

    Terminal
    get_terminal_by_id( int id )
    {
        auto it = std::find_if( this->m_grammar_symbols.terminals( ).begin( ),
                                this->m_grammar_symbols.terminals( ).end( ),
                                [ id ]( const Terminal t ) { return t.id( ) == id; } );
        return *it;
    }

    NonTerminal
    get_non_terminal_by_id( int id )
    {
        auto it = std::find_if( this->m_grammar_symbols.non_terminals( ).begin( ),
                                this->m_grammar_symbols.non_terminals( ).end( ),
                                [ id ]( const NonTerminal t ) { return t.id( ) == id; } );
        return *it;
    }

    static bool
    is_epsilon( Symbol symbol )
    {
        if ( !symbol.is_terminal( ) )
        {
            return false;
        }
        else
        {
            return symbol == Terminal::EPSILON_TERMINAL;
        }
    }

private:
    Counter m_rules_counter;
    std::vector< SyntaxRule > m_grammar_rules;
    GrammarSymbols m_grammar_symbols;
};

#endif  // GRAMMAR_HPP
