#ifndef LEXEMSQUEUE_HPP
#define LEXEMSQUEUE_HPP

#include <vector>
#include <deque>

template < class LexemType >
class Queue
{
    using deque_t = std::deque<LexemType>;

public:
    Queue( );
    template < typename... Args >
    Queue( const Args&... args )
        : deque( { args... } )
    {
    }
    void push_lexem( const LexemType& lexem );
    LexemType pop_lexem( );
    LexemType peek_lexem( ) const;
    typename deque_t::iterator begin( );
    typename deque_t::iterator end( );
    std::vector< LexemType > peek_lexems( int amount ) const;
    std::size_t size( ) const;

private:
    deque_t deque;
};


template < class LexemType >
Queue< LexemType >::Queue( )
{

}

template < class LexemType >
void
Queue< LexemType >::push_lexem( const LexemType& lexem )
{
    deque.push_back( lexem );
}

template < class LexemType >
LexemType
Queue< LexemType >::pop_lexem( )
{
    auto elem = deque.front( );
    deque.pop_front( );
    return elem;
}

template < class LexemType >
LexemType
Queue< LexemType >::peek_lexem( ) const
{
    return deque.front( );
}

template < class LexemType >
typename Queue< LexemType >::deque_t::iterator
Queue< LexemType >::begin( )
{
    return deque.begin( );
}

template < class LexemType >
typename Queue< LexemType >::deque_t::iterator
Queue< LexemType >::end( )
{
    return deque.end( );
}

template < class LexemType >
std::vector< LexemType >
Queue< LexemType >::peek_lexems( int amount ) const
{
}

template < class LexemType >
std::size_t
Queue< LexemType >::size( ) const
{
    return deque.size( );
}

#endif  // LEXEMSQUEUE_HPP
