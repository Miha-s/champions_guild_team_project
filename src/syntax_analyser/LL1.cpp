#include "LL1.hpp"

LL1Analyser::LL1Analyser( SymbolsQueuePtr symbols_queue,
                          OutputStreamPtr output_stream,
                          GrammarPtr grammar )
    : SyntaxAnalyser( symbols_queue, output_stream, grammar )
{
}

void LL1Analyser::process()
{

}

bool LL1Analyser::successfully_parsed() const
{

}

SyntaxAnalyser::FailedState LL1Analyser::get_failed_state() const
{

}
