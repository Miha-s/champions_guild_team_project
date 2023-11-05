#include "RecursiveDescend.hpp"

RecursiveDescend::RecursiveDescend( SymbolsQueuePtr symbols_queue,
                                    OutputStreamPtr output_stream,
                                    GrammarPtr grammar )
    : LL1Parsable( symbols_queue, output_stream, grammar )
{
}

void
RecursiveDescend::process( )
{
    auto table = create_parsing_table( );
    Result rules;
    bool success = process_symbol( m_grammar->initial_symbol( ), table, rules );
    ( *m_output ) << std::endl;
    ( *m_output ) << "Rules: \n" << rules;

    if ( m_queue->size( ) > 1 )
    {
        set_failed_state( m_grammar->epsilon( ), m_queue->peek_lexem( ) );
    }

    m_result = rules;
}

bool
RecursiveDescend::process_symbol( const SymbolPtr& sym, ParsingTable& table, Result& rules )
{
    ( *m_output ) << sym << " -> ";
    if ( sym->is_epsilon( ) )
    {
        return true;
    }

    if ( sym->is_terminal( ) )
    {
        if ( sym == m_queue->peek_lexem( ) )
        {
            m_queue->pop_lexem( );
            return true;
        }
        set_failed_state( sym, m_queue->peek_lexem( ) );
        return false;
    }

    const auto& possible_rules = table[ sym ];
    SyntaxRulePtr found_rule;
    for ( const auto& rule : possible_rules )
    {
        if ( rule.first == m_queue->peek_lexem() )
        {
            found_rule = rule.second;
            break;
        }
    }

    if ( !found_rule )
    {
        set_failed_state( possible_rules, m_queue->peek_lexem( ) );
    }

    rules.push_back( found_rule );
    for ( const auto& sym : found_rule->get_right_side( ) )
    {
        ( *m_output ) << "(";
        bool ok = process_symbol( sym, table, rules );
        ( *m_output ) << ")";
        if ( !ok )
        {
            return false;
        }
    }

    return true;
}
