#ifndef LL1_H
#define LL1_H
#include <unordered_map>
#include "algorithms/algorithms.hpp"
#include "SyntaxAnalyser.hpp"

class LL1Analyser : public SyntaxAnalyser
{
    using ParsingTable =
            std::unordered_map< SymbolPtr, std::unordered_map< SymbolPtr, SyntaxRulePtr > >;

public:
    // SymbolsQueuePtr must have epsilon at the end
    LL1Analyser( SymbolsQueuePtr symbols_queue, OutputStreamPtr output_stream, GrammarPtr grammar );

    void process(  ) override;

private:
    ParsingTable create_parsing_table( );
    SyntaxRules process_sequence( ParsingTable& table );
    void set_failed_state( SymbolPtr expected, SymbolPtr real );
    void set_failed_state( const std::unordered_map< SymbolPtr, SyntaxRulePtr >& expected,
                           SymbolPtr real );
};

#endif // LL1_H
