#ifndef GRAMMAR_HPP
#define GRAMMAR_HPP

#include <vector>
#include <utility>

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

private:

    template < class... Symbols, std::size_t... Is >
    void
    call_add_rule( std::tuple< Symbols... > symbols, std::index_sequence< Is... > )
    {
        m_grammar_symbols.add_symbol( std::get< Is >( symbols )... );
        grammar_rules.push_back(
                SyntaxRule{ m_rules_counter.get_next_id( ), std::get< Is >( symbols )... } );
    }

private:
    Counter m_rules_counter;
    std::vector< SyntaxRule > grammar_rules;
    GrammarSymbols m_grammar_symbols;
};

#endif  // GRAMMAR_HPP
