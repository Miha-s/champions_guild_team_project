#include "LL1.hpp"

#include <stack>

#include "algorithms/algorithms.hpp"

LL1Analyser::LL1Analyser( SymbolsQueuePtr symbols_queue,
                          OutputStreamPtr output_stream,
                          GrammarPtr grammar )
    : LL1Parsable( symbols_queue, output_stream, grammar )
{
}

void
LL1Analyser::process( )
{
    auto table = create_parsing_table( );
    ( *m_output ) << "ParsingTable: \n" << table << std::endl;
    m_result = process_sequence( table );
    ( *m_output ) << "Result: \n" << m_result << std::endl;
}

LL1Analyser::Result
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

    if ( m_queue->size( ) > 1
         || ( m_queue->size( ) == 1 && !m_queue->peek_lexem( )->is_epsilon( ) ) )
    {
        set_failed_state( m_grammar->epsilon( ), m_queue->peek_lexem( ) );
    }

    return rules;
}
