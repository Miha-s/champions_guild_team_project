#ifndef INPUTCOUNTINGDECORATOR_HPP
#define INPUTCOUNTINGDECORATOR_HPP
#include <iostream>
#include <memory>

template < typename InputStream >
class InputCoutingDecorator
{
public:
    using temp = std::istream;
    InputCoutingDecorator( std::shared_ptr< InputStream > stream )
        : m_stream{ stream }
    {
    }

    typename InputStream::int_type
    peek( )
    {
        return m_stream->peek( );
    }

    typename InputStream::int_type
    get( )
    {
        auto tmp = m_stream->get( );
        if ( tmp != '\n' )
        {
            col++;
        }
        else
        {
            col = 0;
            row++;
        }

        return tmp;
    }

    std::pair< size_t, size_t >
    get_position( )
    {
        return { row, col };
    }

private:
    std::shared_ptr< InputStream > m_stream;
    size_t row = 0;
    size_t col = 0;
};

#endif  // INPUTCOUNTINGDECORATOR_HPP
