#include <gtest/gtest.h>

#include <lexer/FiniteAutomataLexer.hpp>

#include "algorithms/algorithms.hpp"
#include "syntax_analyser/LLK.hpp"

class LLKTest : public testing::Test
{
protected:
    void
    SetUp( ) override
    {
        symbols_queue = std::make_shared< SymbolsQueue >( );
        auto dummy_output_stream = std::make_shared< std::ostringstream >( );
        dummy_output = std::static_pointer_cast< std::ostream >( dummy_output_stream );
        grammar = std::make_shared< Grammar >( );
    }

    std::shared_ptr< LLKAnalyser > analyser;
    std::shared_ptr< Grammar > grammar;
    SymbolsQueuePtr symbols_queue;
    OutputStreamPtr dummy_output;
};

TEST_F( LLKTest, test_of_k_parser )
{
    SymbolPtr e = grammar->epsilon( );
    SymbolPtr b_terminal = grammar->define( TerminalGroup::OTHER, TerminalSubgroup::AND );
    SymbolPtr a_terminal = grammar->define( TerminalGroup::COMMENT, TerminalSubgroup::VAR );
    NonTerminalPtr a = grammar->define( NonTerminalType::A );
    NonTerminalPtr b = grammar->define( NonTerminalType::B );
    NonTerminalPtr s = grammar->define( NonTerminalType::S );
    grammar->add_rule( s, a_terminal, b_terminal, a );
    grammar->add_rule( s, e );
    grammar->add_rule( a, s, a_terminal, a_terminal );
    grammar->add_rule( a, b_terminal );
    symbols_queue->push_lexem( a_terminal );
    symbols_queue->push_lexem( b_terminal );
    symbols_queue->push_lexem( a_terminal );
    symbols_queue->push_lexem( a_terminal );
    symbols_queue->push_lexem( b_terminal );
    symbols_queue->push_lexem( b_terminal );
    symbols_queue->push_lexem( a_terminal );
    symbols_queue->push_lexem( a_terminal );
    symbols_queue->push_lexem( e );
    auto expected = std::vector< int >{ 1, 3, 1, 4 };

    analyser = std::make_shared< LLKAnalyser >( symbols_queue, dummy_output, grammar, 2 );
    analyser->process( );

    auto result = analyser->get_result( );
    std::vector< int > actual_ids = { };
    for ( auto rule : result )
    {
        actual_ids.push_back( rule->id( ) );
    }

    ASSERT_EQ( actual_ids, expected );
    ASSERT_TRUE( analyser->successfully_parsed( ) );
}
