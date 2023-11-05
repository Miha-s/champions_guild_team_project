#ifndef LL1PARSABLE_HPP
#define LL1PARSABLE_HPP
#include <unordered_map>
#include "algorithms/algorithms.hpp"
#include "SyntaxAnalyser.hpp"

class LL1Parsable : public SyntaxAnalyser
{
    using ParsingTable =
            std::unordered_map< SymbolPtr, std::unordered_map< SymbolPtr, SyntaxRulePtr > >;

public:
    // SymbolsQueuePtr must have epsilon at the end
    LL1Parsable( SymbolsQueuePtr symbols_queue, OutputStreamPtr output_stream, GrammarPtr grammar );


protected:
    ParsingTable create_parsing_table( );

    void set_failed_state( SymbolPtr expected, SymbolPtr real );
    void set_failed_state( const std::unordered_map< SymbolPtr, SyntaxRulePtr >& expected,
                           SymbolPtr real );
};

#endif  // LL1PARSABLE_HPP
