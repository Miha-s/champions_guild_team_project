#ifndef RECURSIVEDESCEND_HPP
#define RECURSIVEDESCEND_HPP

#include <unordered_map>
#include "algorithms/algorithms.hpp"
#include "LL1Parsable.hpp"

class RecursiveDescend : public LL1Parsable
{
    using ParsingTable =
            std::unordered_map< SymbolPtr, std::unordered_map< SymbolPtr, SyntaxRulePtr > >;

public:
    // SymbolsQueuePtr must have epsilon at the end
    RecursiveDescend( SymbolsQueuePtr symbols_queue, OutputStreamPtr output_stream, GrammarPtr grammar );

    void process(  ) override;

private:
    bool process_symbol( const SymbolPtr& sym, ParsingTable& table, Result& rules );
};


#endif // RECURSIVEDESCEND_HPP
