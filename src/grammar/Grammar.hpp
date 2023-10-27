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

    template < class... Symbols >
    void
    add_rule( const Symbols&... symbols )
    {
        std::tuple< Symbols... > copied_symbols( symbols... );
        call_add_rule( copied_symbols, std::index_sequence_for< Symbols... >( ) );
    }

    Terminal
    get_symbol( TerminalGroup group, TerminalSubgroup subgroup ) const
    {
        return m_grammar_symbols.get_terminal( group, subgroup );
    }

    NonTerminal
    get_symbol( NonTerminalGroup group, NonTerminalSubgroup subgroup ) const
    {
        return m_grammar_symbols.get_non_terminal( group, subgroup );
    }

    SyntaxRule
    get_rule( SymbolId id )
    {
        auto it = std::find_if( m_grammar_rules.begin( ),
                                m_grammar_rules.end( ),
                                [ id ]( const SyntaxRule& rule ) { return rule.id( ) == id; } );

        return it == m_grammar_rules.end( ) ? INVALID_RULE : *it;
    }

private:
    template < class... Symbols, std::size_t... Is >
    void
    call_add_rule( std::tuple< Symbols... >& symbols, std::index_sequence< Is... > )
    {
        m_grammar_symbols.add_symbol( std::get< Is >( symbols )... );
        m_grammar_rules.push_back(
                SyntaxRule{ m_rules_counter.get_next_id( ), std::get< Is >( symbols )... } );
    }

private:
    Counter m_rules_counter;
    std::vector< SyntaxRule > m_grammar_rules;
    GrammarSymbols m_grammar_symbols;
};

#endif  // GRAMMAR_HPP
