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
    auto table = create_parsing_table( );
    LLKElement first_element;
    first_element.table = table;
    m_result = process_sequence( first_element );
}

LLKAnalyser::LLKTablePtr
LLKAnalyser::create_parsing_table( )
{
    std::deque< ParsingTableStackElement > parsing_queue;
    ParsingTableStackElement initial;
    initial.table = empty_table( );
    initial.symbol = m_grammar->initial_symbol( );
    SymbolsSet l;
    l.insert( { m_grammar->epsilon( ) } );
    initial.l = l;
    parsing_queue.push_back(initial);

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
        updated = false;
        auto parsing_table = parsing_queue.front( );
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
                SymbolsSet l_next;
                if (symbol_it + 1 != right_side.end())
                    l_next = first_k( *m_grammar, k, symbol_it+1, right_side.end( ) );
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
                    parsing_queue.push_back( next_table );
                    parsed_tables.push_back( next_table );
                }

                table_element.elements.push_back( llk_element );
            }

            for ( auto sequence : u )
            {
                parsing_table.table->map[ sequence ] = table_element;
            }
        }
        parsing_queue.pop_front();
    }

    return initial.table;
}

SyntaxAnalyser::Result
LLKAnalyser::process_sequence( LLKElement first_element )
{
    std::stack< LLKElement > processing_stack;
    SymbolsQueue current_symbols;
    SyntaxRules rules;

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

    while ( processing_stack.size( ) > 0 && current_symbols.size( ) > 0 )
    {
        auto current_element = processing_stack.top( );
        if ( current_element.symbol )
        {
            if ( current_element.symbol == current_symbols.peek_lexem( ) )
            {
                current_symbols.pop_lexem( );
                if ( m_queue->size( ) )
                {
                    current_symbols.push_lexem( m_queue->peek_lexem( ) );
                    m_queue->pop_lexem( );
                }
                processing_stack.pop( );
                continue;
            }
            else
            {
                set_failed_state( current_element.symbol, current_symbols.peek_lexem( ) );
            }
        }
        auto current_symbols_sequence = Symbols{ current_symbols.begin( ), current_symbols.end( ) };
        auto table_element = current_element.table->map[ current_symbols_sequence ];

        if ( !table_element.syntax_rule )
        {
            set_failed_state( current_element.table, current_symbols_sequence );
        }

        rules.push_back( table_element.syntax_rule );

        processing_stack.pop( );

        std::for_each(
                table_element.elements.crbegin( ),
                table_element.elements.crend( ),
                [ &processing_stack ]( const LLKElement& sym ) { processing_stack.push( sym ); } );

        if ( processing_stack.size( ) > 1 && current_element.symbol
             && current_element.symbol->is_epsilon( ) )
        {
            processing_stack.pop( );
        }
    }

    return rules;
}

void
LLKAnalyser::set_failed_state( SymbolPtr expected, SymbolPtr real )
{
    SymbolsSet expected_symbols;
    m_failed_state.expected.insert( { expected } );
    m_failed_state.real = { real };
}

void
LLKAnalyser::set_failed_state( const LLKTablePtr& expected, Symbols real )
{
    for ( const auto& symbols : expected->map )
    {
        m_failed_state.expected.insert( symbols.first );
    }
    m_failed_state.real = real;
}

LLKAnalyser::LLKTablePtr
LLKAnalyser::empty_table( ) const
{
    return std::make_shared< LLKTable >( );
}
