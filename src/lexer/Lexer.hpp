#ifndef LEXER_HPP
#define LEXER_HPP
#include <iostream>
#include <memory>
#include "structures/LexemsQueue.hpp"
#include "grammar/Terminal.hpp"
#include "grammar/Grammar.hpp"
#include "structures/InputCountingDecorator.hpp"

using TerminalsQueue = LexemsQueue< Terminal >;
using TerminalsQueuePtr = std::shared_ptr< TerminalsQueue >;
using InputStream = InputCoutingDecorator< std::istream >;
using InputStreamPtr = std::shared_ptr< InputStream >;
using OutputStreamPtr = std::shared_ptr< std::ostream >;
using GrammarPtr = std::shared_ptr< Grammar >;

class Lexer
{
public:
    using FailedState = int;

    Lexer( InputStreamPtr input,
           TerminalsQueuePtr queue,
           OutputStreamPtr output,
           GrammarPtr grammar )
        : m_input( input )
        , m_queue( queue )
        , m_output( output )
        , m_grammar( grammar )
    {
    }

    virtual void process( ) = 0;

    virtual bool successfully_parsed( ) const = 0;
    virtual FailedState get_failed_state( ) const = 0;
protected:
    InputStreamPtr m_input;
    TerminalsQueuePtr m_queue;
    OutputStreamPtr m_output;
    GrammarPtr m_grammar;
};

#endif  // LEXER_HPP
