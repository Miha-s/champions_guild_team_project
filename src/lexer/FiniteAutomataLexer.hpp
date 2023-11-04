#ifndef FINITEAUTOMATALEXER_H
#define FINITEAUTOMATALEXER_H

#include "Lexer.hpp"


class FiniteAutomataLexer : public Lexer
{
    bool m_success = false;

public:
    FiniteAutomataLexer( InputStreamPtr input,
                         LexemsQueuePtr queue,
                         OutputStreamPtr output,
                         GrammarPtr grammar );

    void process(  ) override;

    bool successfully_parsed( ) const override;
    FailedState get_failed_state( ) const override;
private:
    using LexemPtr = std::shared_ptr< Lexem >;

    LexemPtr read_next_lexem( );

    Lexem read_number_lexem( );
    Lexem read_letter_lexem( );
    Lexem read_operator_lexem( );
};

#endif // FINITEAUTOMATALEXER_H
