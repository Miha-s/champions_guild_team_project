#include "LLK.hpp"

#include <stack>

LLKAnalyser::LLKAnalyser( SymbolsQueuePtr symbols_queue,
                          OutputStreamPtr output_stream,
                          GrammarPtr grammar,
                          size_t k )
    : SyntaxAnalyser( symbols_queue, output_stream, grammar )
    , k{ k }
{
}

void
LLKAnalyser::process( )
{
}

LLKAnalyser::LLKTablePtr
LLKAnalyser::create_parsing_table( )
{
    std::stack< ParsingTableStackElement > parsing_stack;
    ParsingTableStackElement initial;
    initial.table = empty_table( );
    initial.symbol = m_grammar->initial_symbol( );
    SymbolsSet l;
    l.insert( { m_grammar->epsilon( ) } );
    initial.l = l;

    std::vector< ParsingTableStackElement > parsed_tables;
    parsed_tables.push_back( initial );

    auto find_in_existing_tables = [ &parsed_tables ]( const SymbolPtr& sym,
                                                       const SymbolsSet& sym_set ) {
        return std::find_if( parsed_tables.begin( ),
                             parsed_tables.end( ),
                             [ & ]( const ParsingTableStackElement& el ) {
                                 return el.l == sym_set && el.symbol == sym;
                             } );
    };

    bool updated = true;
    while ( updated )
    {
        auto parsing_table = parsing_stack.top( );
        for ( const auto& rule : m_grammar->syntax_rules_from_symbol( parsing_table.symbol ) )
        {
            auto u = first_k( *m_grammar, k, rule->get_right_side( ) );
            u.add_k( parsing_table.l, k );

            LLKTableElement table_element;
            table_element.syntax_rule = rule;
            auto right_side = rule->get_right_side( );

            for ( auto symbol_it = right_side.begin( ); symbol_it != right_side.end( );
                  symbol_it++ )
            {
                LLKElement llk_element;
                if ( !( *symbol_it )->is_non_terminal( ) )
                {
                    llk_element.symbol = *symbol_it;
                    table_element.elements.push_back( llk_element );
                    continue;
                }

                auto l_next = first_k( *m_grammar, k, symbol_it++, right_side.end( ) );
                l_next.add_k( parsing_table.l, k );

                ParsingTableStackElement next_table;
                next_table.l = l_next;
                next_table.table = empty_table( );
                next_table.symbol = *symbol_it;

                auto existing_table = find_in_existing_tables( next_table.symbol, next_table.l );

                if ( existing_table != parsed_tables.end( ) )
                {
                    llk_element.table = existing_table->table;
                }
                else
                {
                    updated = true;
                    llk_element.table = next_table.table;
                    parsing_stack.push( next_table );
                    parsed_tables.push_back( next_table );
                }

                table_element.elements.push_back( llk_element );
            }

            for ( auto sequence : u )
            {
                parsing_table.table->map[ sequence ] = table_element;
            }
        }
    }

    return initial.table;
}

SyntaxAnalyser::Result
LLKAnalyser::process_sequence( LLKTableElement first_element )
{
    std::stack< LLKTableElement > processing_stack;
    SymbolsQueue current_symbols;

    for ( int i = 0; i < k; i++ )
    {
        if ( m_queue->size( ) == 0 )
        {
            break;
        }
        current_symbols.push_lexem( m_queue->peek_lexem( ) );
        m_queue->pop_lexem( );
    }

    processing_stack.push( first_element );

    while()
}

LLKAnalyser::LLKTablePtr
LLKAnalyser::empty_table( ) const
{
    return std::make_shared< LLKTable >( );
}
