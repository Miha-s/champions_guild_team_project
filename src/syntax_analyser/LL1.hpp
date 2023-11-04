#ifndef LL1_H
#define LL1_H
#include <unordered_map>
#include "SyntaxAnalyser.hpp"

class LL1Analyser : public SyntaxAnalyser
{
    using ParsingTable = std::unordered_map<SymbolPtr, std::unordered_map<SymbolPtr, SyntaxRule>>;
public:
    LL1Analyser( SymbolsQueuePtr symbols_queue, OutputStreamPtr output_stream, GrammarPtr grammar );

    void process(  ) override;

    bool successfully_parsed( ) const override;
    FailedState get_failed_state( ) const override;
private:

};

#endif // LL1_H
