#ifndef SYNTAXANALYSER_HPP
#define SYNTAXANALYSER_HPP

class SyntaxAnalyser {
    using FailedState = int;
    using Result = int;
public:
    virtual void process( ) = 0;
    virtual bool successfully_parsed( ) const = 0;
    virtual FailedState get_failed_state( ) const = 0;
    virtual Result get_result( ) const = 0;
};

#endif // SYNTAXANALYSER_HPP
