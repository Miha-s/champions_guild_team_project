#ifndef LLK_H
#define LLK_H
#include <unordered_map>
#include "algorithms/algorithms.hpp"
#include "SyntaxAnalyser.hpp"

class LLKAnalyser : public SyntaxAnalyser
{
    struct LLKTable;
    using LLKTablePtr = std::shared_ptr< LLKTable >;

    struct LLKElement
    {
        SymbolPtr symbol;
        LLKTablePtr table;
    };

    struct LLKTableElement {
        SyntaxRulePtr syntax_rule;
        std::vector< LLKElement > elements;
    };

    struct LLKTable
    {
        using LLKTableMap = std::unordered_map< Symbols, LLKTableElement, SymbolsHash >;
        LLKTableMap map;
    };

public:
    // SymbolsQueuePtr must have epsilon at the end
    LLKAnalyser( SymbolsQueuePtr symbols_queue, OutputStreamPtr output_stream, GrammarPtr grammar, size_t k );

    void process(  ) override;

private:
    struct ParsingTableStackElement
    {
        LLKTablePtr table;
        SymbolPtr symbol;
        SymbolsSet l;
    };

    LLKTablePtr create_parsing_table( );
    Result process_sequence( LLKTableElement first_element );
    void set_failed_state( SymbolPtr expected, SymbolPtr real );
    void set_failed_state( const std::unordered_map< SymbolPtr, SyntaxRulePtr >& expected,
                           SymbolPtr real );

    LLKTablePtr empty_table() const;

    size_t k;

};

#endif // LLK_H
