#ifndef FINITEAUTOMATALEXER_H
#define FINITEAUTOMATALEXER_H

#include "Lexer.hpp"


class FiniteAutomataLexer : public Lexer
{
    bool m_success = false;

public:
    FiniteAutomataLexer( InputStreamPtr input,
                         TerminalsQueuePtr queue,
                         OutputStreamPtr output,
                         GrammarPtr grammar );

    void process(  ) override;

    bool successfully_parsed( ) const override;
    FailedState get_failed_state( ) const override;
private:
    using TerminalPtr = std::shared_ptr< Terminal >;

    TerminalPtr read_next_lexem( );

    Terminal read_number_lexem( );
    Terminal read_letter_lexem( );
    Terminal read_operator_lexem( );
};

#endif // FINITEAUTOMATALEXER_H
