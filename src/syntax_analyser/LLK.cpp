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

LLKAnalyser::LLKTablePtr
LLKAnalyser::create_parsing_table( )
{
    std::stack< ParsingStackElement > parsing_stack;
    ParsingStackElement initial;
    initial.table = empty_table( );
    initial.symbol = m_grammar->initial_symbol();
    SymbolsSet l;
    l.insert( { m_grammar->epsilon( ) } );
    initial.l = l;

    bool updated = true;
    while ( updated )
    {
        auto parsing_table = parsing_stack.top( );
        for ( const auto& rule : m_grammar->syntax_rules_from_symbol( parsing_table.symbol ) )
        {
            auto u = first_k( *m_grammar, k, rule->get_right_side( ) );
            u.add_k( parsing_table.l, k );

        }
    }
}

LLKAnalyser::LLKTablePtr LLKAnalyser::empty_table() const
{
    return std::make_shared< LLKTable >( );
}
