#ifndef LEXER_HPP
#define LEXER_HPP
#include <iostream>
#include <memory>
#include "structures/LexemsQueue.hpp"
#include "Lexem.hpp"
#include "grammar/Grammar.hpp"
#include "structures/InputCountingDecorator.hpp"

using LexemsQueue = Queue< Lexem >;
using LexemsQueuePtr = std::shared_ptr< LexemsQueue >;
using InputStream = InputCoutingDecorator< std::istream >;
using InputStreamPtr = std::shared_ptr< InputStream >;
using OutputStreamPtr = std::shared_ptr< std::ostream >;
using GrammarPtr = std::shared_ptr< Grammar >;

class Lexer
{
public:
    using FailedState = int;

    Lexer( InputStreamPtr input,
           LexemsQueuePtr queue,
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
    LexemsQueuePtr m_queue;
    OutputStreamPtr m_output;
    GrammarPtr m_grammar;
};

#endif  // LEXER_HPP
