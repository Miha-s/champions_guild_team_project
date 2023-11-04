#ifndef SYNTAXANALYSER_HPP
#define SYNTAXANALYSER_HPP

#include "structures/Queue.hpp"
#include "grammar/Symbol.hpp"
#include "grammar/Grammar.hpp"
#include "algorithms/algorithms.hpp"

using SymbolsQueue = Queue< SymbolPtr >;
using SymbolsQueuePtr = std::shared_ptr< SymbolsQueue >;
using OutputStreamPtr = std::shared_ptr< std::ostream >;
using GrammarPtr = std::shared_ptr< Grammar >;

class SyntaxAnalyser
{
public:
    struct FailedState
    {
        SymbolsSet expected;
        Symbols real;
    };
    using Result = SyntaxRules;

    SyntaxAnalyser( SymbolsQueuePtr symbols_queue,
                    OutputStreamPtr output_stream,
                    GrammarPtr grammar )
        : m_queue( symbols_queue )
        , m_output( output_stream )
        , m_grammar( grammar )
    {
    }

    virtual void process( ) = 0;

    bool
    successfully_parsed( ) const
    {
        return m_failed_state.expected.size( ) == 0;
    };

    FailedState
    get_failed_state( ) const
    {
        return m_failed_state;
    }

    virtual Result
    get_result( ) const
    {
        return m_result;
    }

protected:
    SymbolsQueuePtr m_queue;
    OutputStreamPtr m_output;
    GrammarPtr m_grammar;
    FailedState m_failed_state;
    Result m_result;
};

#endif  // SYNTAXANALYSER_HPP
