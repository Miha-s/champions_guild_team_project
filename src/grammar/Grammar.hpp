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

    TerminalPtr
    define( TerminalGroup group, TerminalSubgroup subgroup )
    {
        return m_grammar_symbols.define( group, subgroup );
    }

    NonTerminalPtr
    define( NonTerminalType type )
    {
        return m_grammar_symbols.define( type );
    }

    TerminalPtr
    create( TerminalGroup group, TerminalSubgroup subgroup ) const
    {
        return m_grammar_symbols.get_terminal( group, subgroup );
    }

    NonTerminalPtr
    create( NonTerminalType type ) const
    {
        return m_grammar_symbols.get_non_terminal( type );
    }

    template < class... SymbolsT >
    void
    add_rule( const SymbolsT&... symbols )
    {
        m_grammar_rules.push_back( SyntaxRule{ m_rules_counter.get_next_id( ), symbols... } );
    }

    SyntaxRule
    get_rule( SymbolId id ) const
    {
        auto it = std::find_if( m_grammar_rules.cbegin( ),
                                m_grammar_rules.cend( ),
                                [ id ]( const SyntaxRule& rule ) { return rule.id( ) == id; } );

        return it == m_grammar_rules.end( ) ? INVALID_RULE : *it;
    }

    std::unordered_set< NonTerminalPtr >
    get_non_terminals( ) const
    {
        return this->m_grammar_symbols.non_terminals( );
    }

    std::vector< SyntaxRule >
    get_grammar_rules( ) const
    {
        return this->m_grammar_rules;
    }

    TerminalPtr
    get_terminal_by_id( int id ) const
    {
        auto it = std::find_if( this->m_grammar_symbols.terminals( ).cbegin( ),
                                this->m_grammar_symbols.terminals( ).cend( ),
                                [ id ]( const TerminalPtr& t ) { return t->id( ) == id; } );
        return *it;
    }

    NonTerminalPtr
    get_non_terminal_by_id( int id ) const
    {
        auto it = std::find_if( this->m_grammar_symbols.non_terminals( ).cbegin( ),
                                this->m_grammar_symbols.non_terminals( ).cend( ),
                                [ id ]( const NonTerminalPtr t ) { return t->id( ) == id; } );
        return *it;
    }

    std::shared_ptr< const Epsilon >
    epsilon( )
    {
        return m_grammar_symbols.epsilon( );
    }

private:
    Counter m_rules_counter;
    std::vector< SyntaxRule > m_grammar_rules;
    GrammarSymbols m_grammar_symbols;
};

#endif  // GRAMMAR_HPP
