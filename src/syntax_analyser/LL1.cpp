#include "LL1.hpp"

#include <stack>

#include "algorithms/algorithms.hpp"

LL1Analyser::LL1Analyser( SymbolsQueuePtr symbols_queue,
                          OutputStreamPtr output_stream,
                          GrammarPtr grammar )
    : SyntaxAnalyser( symbols_queue, output_stream, grammar )
{
}

void
LL1Analyser::process( )
{
    auto table = create_parsing_table( );
    m_result = process_sequence( table );
}

LL1Analyser::ParsingTable
LL1Analyser::create_parsing_table( )
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
    }

    return table;
}

SyntaxRules
LL1Analyser::process_sequence( ParsingTable& table )
{
    std::stack< SymbolPtr > current_stack;
    SyntaxRules rules;
    current_stack.push( m_grammar->get_grammar_rules( )[ 0 ]->get_left_side( ) );

    while ( m_queue->size( ) > 0 && current_stack.size( ) > 0 )
    {
        const auto& stack_symbol = current_stack.top( );
        const auto& queue_symbol = m_queue->peek_lexem( );

        if ( stack_symbol->is_terminal( ) || stack_symbol->is_epsilon( ) )
        {
            if ( queue_symbol == stack_symbol )
            {
                if ( !queue_symbol->is_epsilon( ) )
                {
                    m_queue->pop_lexem( );
                }
                current_stack.pop( );
                continue;
            }
            else
            {
                set_failed_state( stack_symbol, queue_symbol );
                break;
            }
        }

        // if non_terminal
        const auto& rule = table[ stack_symbol ][ queue_symbol ];

        if ( !rule->is_valid( ) )
        {
            set_failed_state( table[ stack_symbol ], queue_symbol );
            break;
        }

        current_stack.pop( );
        rules.push_back( rule );

        auto right_side = rule->get_right_side( );

        std::for_each( right_side.crbegin( ),
                       right_side.crend( ),
                       [ &current_stack ]( const SymbolPtr& sym ) { current_stack.push( sym ); } );

        if ( current_stack.size( ) > 1 && stack_symbol->is_epsilon( ) )
        {
            current_stack.pop();
        }
    }
    return rules;
}

void
LL1Analyser::set_failed_state( SymbolPtr expected, SymbolPtr real )
{
    SymbolsSet expected_symbols;
    m_failed_state.expected.insert( { expected } );
    m_failed_state.real = real;
}

void
LL1Analyser::set_failed_state( const std::unordered_map< SymbolPtr, SyntaxRulePtr >& expected,
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

    m_failed_state.real = real;
}
