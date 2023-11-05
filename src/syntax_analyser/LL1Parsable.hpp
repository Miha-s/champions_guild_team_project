#ifndef LL1PARSABLE_HPP
#define LL1PARSABLE_HPP
#include <unordered_map>
#include "algorithms/algorithms.hpp"
#include "SyntaxAnalyser.hpp"

class LL1Parsable : public SyntaxAnalyser
{
protected:
    using ParsingTable = std::unordered_map< SymbolPtr, SymbolRuleMap >;

public:
    // SymbolsQueuePtr must have epsilon at the end
    LL1Parsable( SymbolsQueuePtr symbols_queue, OutputStreamPtr output_stream, GrammarPtr grammar );


protected:
    ParsingTable create_parsing_table( );

    void set_failed_state( SymbolPtr expected, SymbolPtr real );
    void set_failed_state( const SymbolRuleMap& expected,
                           SymbolPtr real );

    friend std::ostream& operator<<( std::ostream& os, const ParsingTable& table );
};

std::ostream& operator<<( std::ostream& os, const SymbolRuleMap& table );

std::ostream& operator<<( std::ostream& os, const LL1Parsable::ParsingTable& table );

#endif  // LL1PARSABLE_HPP
