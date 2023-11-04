#ifndef SYNTAXANALYSER_HPP
#define SYNTAXANALYSER_HPP

#include "structures/Queue.hpp"
#include "grammar/Symbol.hpp"
#include "grammar/Grammar.hpp"

using SymbolsQueue = Queue< SymbolPtr >;
using SymbolsQueuePtr = std::shared_ptr< SymbolsQueue >;
using OutputStreamPtr = std::shared_ptr< std::ostream >;
using GrammarPtr = std::shared_ptr< Grammar >;

class SyntaxAnalyser
{
public:
    using FailedState = int;
    using Result = int;

    SyntaxAnalyser( SymbolsQueuePtr symbols_queue,
                    OutputStreamPtr output_stream,
                    GrammarPtr grammar )
        : m_queue( symbols_queue )
        , m_output( output_stream )
        , m_grammar( grammar )
    {
    }

    virtual void process( ) = 0;
    virtual bool successfully_parsed( ) const = 0;
    virtual FailedState get_failed_state( ) const = 0;
    virtual Result get_result( ) const = 0;
protected:
    SymbolsQueuePtr m_queue;
    OutputStreamPtr m_output;
    GrammarPtr m_grammar;
};

#endif  // SYNTAXANALYSER_HPP
