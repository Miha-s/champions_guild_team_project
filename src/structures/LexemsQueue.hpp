#ifndef LEXEMSQUEUE_HPP
#define LEXEMSQUEUE_HPP

#include <vector>

template < class LexemType >
class LexemsQueue
{
public:
    void push_lexem( const LexemType& lexem );
    LexemType pop_lexem( );
    LexemType peek_lexem( );
    std::vector< LexemType > peek_lexems( int amount );
};

#endif  // LEXEMSQUEUE_HPP
