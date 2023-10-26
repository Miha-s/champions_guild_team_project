#ifndef LEXER_HPP
#define LEXER_HPP
#include <istream>

class Lexer {
    using FailedState = int;
    using Result = int;
public:
    virtual void process( std::istream i_stream ) = 0;
    virtual bool successfully_parsed() const = 0;
    virtual FailedState get_failed_state( ) const = 0;
    virtual Result get_result( ) const = 0;
};

#endif // LEXER_HPP
