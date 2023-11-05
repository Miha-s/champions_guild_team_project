#include <iostream>
#include <sstream>

#include "syntax_analyser/LL1.hpp"
#include "syntax_analyser/LLK.hpp"
#include "syntax_analyser/RecursiveDescend.hpp"

enum SyntaxAnalyserType
{
    LLK,
    LL1,
    Recursive
};

void
run_parser( GrammarPtr grammar, SymbolsQueuePtr queue, SyntaxAnalyserType type, size_t k = 1 )
{
    auto output_stream = std::make_shared< std::ostringstream >( );
    auto output = std::static_pointer_cast< std::ostream >( output_stream );

    std::shared_ptr< SyntaxAnalyser > analysator;
    if ( type == LLK )
    {
        analysator = std::make_shared< LLKAnalyser >( queue, output, grammar, k );
    }
    else if ( type == LL1 )
    {
        analysator = std::make_shared< LL1Analyser >( queue, output, grammar );
    }
    else
    {
        analysator = std::make_shared< RecursiveDescend >( queue, output, grammar );
    }

    auto initial_sequence = Symbols( queue->begin( ), queue->end( ) );

    analysator->process( );

    std::cout << output_stream->str( );
    std::cout << "Rules expantion: " << std::endl;

    expand_rules_sequence( *grammar, std::cout, analysator->get_result( ) );

    std::cout << std::endl;
    std::cout << "Initial sequence: " << initial_sequence << std::endl << std::endl;

    if ( !analysator->successfully_parsed( ) )
    {
        std::cout << "Failed to parse: " << std::endl;
        std::cout << "Was expecting any of: " << analysator->get_failed_state( ).expected
                  << std::endl;
        std::cout << "Instead got: " << analysator->get_failed_state( ).real << std::endl;
    }
}

void
llk_usecase( )
{
    auto grammar = std::make_shared< Grammar >( );

    auto e = grammar->epsilon( );
    auto a = grammar->define( TerminalGroup::t, TerminalSubgroup::a );
    auto b = grammar->define( TerminalGroup::t, TerminalSubgroup::b );
    auto S = grammar->define( NonTerminalType::S );
    auto A = grammar->define( NonTerminalType::A );

    grammar->add_rule( S, a, b, A );
    grammar->add_rule( S, e );
    grammar->add_rule( A, S, a, a );
    grammar->add_rule( A, b );

    auto lexems_queue = std::make_shared< SymbolsQueue >( a, b, a, b, b, a, a, e );
    run_parser( grammar, lexems_queue, LLK, 2 );
}

void
ll1_grammar( SyntaxAnalyserType type )
{
    auto grammar = std::make_shared< Grammar >( );

    auto e = grammar->epsilon( );
    auto a = grammar->define( TerminalGroup::t, TerminalSubgroup::a );
    auto plus = grammar->define( TerminalGroup::t, TerminalSubgroup::PLUS );
    auto mul = grammar->define( TerminalGroup::t, TerminalSubgroup::MULTIPLY );
    auto left = grammar->define( TerminalGroup::t, TerminalSubgroup::ROUND_LEFT );
    auto right = grammar->define( TerminalGroup::t, TerminalSubgroup::ROUND_RIGHT );

    auto S = grammar->define( NonTerminalType::S );
    auto A = grammar->define( NonTerminalType::A );
    auto B = grammar->define( NonTerminalType::B );
    auto C = grammar->define( NonTerminalType::C );
    auto D = grammar->define( NonTerminalType::D );

    grammar->add_rule( S, B, A );
    grammar->add_rule( A, plus, B, A );
    grammar->add_rule( A, e );
    grammar->add_rule( B, D, C );
    grammar->add_rule( C, mul, D, C );
    grammar->add_rule( C, e );
    grammar->add_rule( D, left, S, right );
    grammar->add_rule( D, a );

    auto lexems_queue = std::make_shared< SymbolsQueue >( left, a, plus, a, right, mul, a, e );

    run_parser( grammar, lexems_queue, type );
}

void
ll1_usecase( )
{
    ll1_grammar( LL1 );
}

void
recursive_usecase( )
{
    ll1_grammar( Recursive );
}

int
main( )
{
    llk_usecase( );
    return 0;
}
