#ifndef LEXEMSQUEUE_HPP
#define LEXEMSQUEUE_HPP

#include <vector>
#include <deque>

template < class LexemType >
class LexemsQueue
{
public:
    void push_lexem( const LexemType& lexem );
    LexemType pop_lexem( );
    LexemType peek_lexem( ) const;
    std::vector< LexemType > peek_lexems( int amount ) const;
    std::size_t size( ) const;

private:
    std::deque< LexemType > deque;
};

template < class LexemType >
void
LexemsQueue< LexemType >::push_lexem( const LexemType& lexem )
{
    deque.push_back( lexem );
}

template < class LexemType >
LexemType
LexemsQueue< LexemType >::pop_lexem( )
{
    auto elem = deque.front( );
    deque.pop_front( );
    return elem;
}

template < class LexemType >
LexemType
LexemsQueue< LexemType >::peek_lexem( ) const
{
    deque.front( );
}

template < class LexemType >
std::vector< LexemType >
LexemsQueue< LexemType >::peek_lexems( int amount ) const
{
}

template < class LexemType >
std::size_t
LexemsQueue< LexemType >::size( ) const
{
    return deque.size( );
}

#endif  // LEXEMSQUEUE_HPP
