#ifndef LL1_H
#define LL1_H
#include <unordered_map>
#include "algorithms/algorithms.hpp"
#include "LL1Parsable.hpp"

class LL1Analyser : public LL1Parsable
{
public:
    // SymbolsQueuePtr must have epsilon at the end
    LL1Analyser( SymbolsQueuePtr symbols_queue, OutputStreamPtr output_stream, GrammarPtr grammar );

    void process(  ) override;

private:
    Result process_sequence( ParsingTable& table );
};

#endif // LL1_H
