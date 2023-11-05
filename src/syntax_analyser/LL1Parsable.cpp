#include "LL1Parsable.hpp"

LL1Parsable::LL1Parsable( SymbolsQueuePtr symbols_queue,
                          OutputStreamPtr output_stream,
                          GrammarPtr grammar )
    : SyntaxAnalyser( symbols_queue, output_stream, grammar )
{
}

LL1Parsable::ParsingTable LL1Parsable::create_parsing_table()
{
    std::unordered_map< SyntaxRulePtr, SymbolsSet > rules_map;
    size_t k = 1;
    auto firstSets = first_k( *m_grammar, k );
    auto followSets = follow_k( *m_grammar, k );

    for ( const auto& rule : m_grammar->get_grammar_rules( ) )
    {
        SymbolsSet tmp_set;
        for ( const auto& symbol : rule->get_right_side( ) )
        {
            tmp_set.add_k( firstSets[ symbol ], k );
        }
        tmp_set.add_k( followSets[ rule->get_left_side( ) ], k );
        rules_map[ rule ] = tmp_set;
    }

    ParsingTable table;
    for ( const auto& non_terminal : m_grammar->get_non_terminals( ) )
    {
        for ( const auto& terminal : m_grammar->get_terminals( ) )
        {
            table[ non_terminal ][ terminal ] = SyntaxRule::InvalidRule( );
        }
        table[ non_terminal ][ m_grammar->epsilon( ) ] = SyntaxRule::InvalidRule( );
    }

    for ( const auto& rule : m_grammar->get_grammar_rules( ) )
    {
        for ( const auto& terminal : m_grammar->get_terminals( ) )
        {
            if ( rules_map[ rule ].contains( { terminal } ) )
            {
                table[ rule->get_left_side( ) ][ terminal ] = rule;
            }
        }
        if ( rules_map[ rule ].contains( { m_grammar->epsilon( ) } ) )
        {
            table[ rule->get_left_side( ) ][ m_grammar->epsilon( ) ] = rule;
        }
    }

    return table;
}

void
LL1Parsable::set_failed_state( SymbolPtr expected, SymbolPtr real )
{
    SymbolsSet expected_symbols;
    m_failed_state.expected.insert( { expected } );
    m_failed_state.real = { real };
}

void
LL1Parsable::set_failed_state( const std::unordered_map< SymbolPtr, SyntaxRulePtr >& expected,
                               SymbolPtr real )
{
    SymbolsSet expected_symbols;
    for ( const auto& sym : expected )
    {
        if ( sym.second->is_valid( ) )
        {
            m_failed_state.expected.insert( { sym.first } );
        }
    }

    m_failed_state.real = { real };
}
