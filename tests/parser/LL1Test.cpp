#include <gtest/gtest.h>

#include <lexer/FiniteAutomataLexer.hpp>

#include "algorithms/algorithms.hpp"
#include "syntax_analyser/LL1.hpp"

class LL1Test : public testing::Test
{
protected:
    void
    SetUp( ) override
    {
        symbols_queue = std::make_shared< SymbolsQueue >( );
        string_stream = std::make_shared< std::ostringstream >( );
        dummy_output = std::static_pointer_cast< std::ostream >( string_stream );
        grammar = std::make_shared< Grammar >( );
    }

    std::shared_ptr< LL1Analyser > analyser;
    std::shared_ptr< Grammar > grammar;
    SymbolsQueuePtr symbols_queue;
    std::shared_ptr< std::ostringstream > string_stream;
    OutputStreamPtr dummy_output;
};

TEST_F( LL1Test, test_of_parser )
{
    SymbolPtr e = grammar->epsilon( );
    SymbolPtr plus = grammar->define( TerminalGroup::OTHER, TerminalSubgroup::PLUS );
    SymbolPtr andd = grammar->define( TerminalGroup::OTHER, TerminalSubgroup::AND );
    SymbolPtr round_left = grammar->define( TerminalGroup::OTHER, TerminalSubgroup::ROUND_LEFT );
    SymbolPtr round_right = grammar->define( TerminalGroup::OTHER, TerminalSubgroup::ROUND_RIGHT );
    SymbolPtr a_terminal = grammar->define( TerminalGroup::COMMENT, TerminalSubgroup::VAR );
    NonTerminalPtr a = grammar->define( NonTerminalType::A );
    NonTerminalPtr b = grammar->define( NonTerminalType::B );
    NonTerminalPtr c = grammar->define( NonTerminalType::C );
    NonTerminalPtr d = grammar->define( NonTerminalType::D );
    NonTerminalPtr s = grammar->define( NonTerminalType::S );
    grammar->add_rule( s, b, a );
    grammar->add_rule( a, plus, b, a );
    grammar->add_rule( a, e );
    grammar->add_rule( b, d, c );
    grammar->add_rule( c, andd, d, c );
    grammar->add_rule( c, e );
    grammar->add_rule( d, round_left, s, round_right );
    grammar->add_rule( d, a_terminal );
    symbols_queue->push_lexem( round_left );
    symbols_queue->push_lexem( a_terminal );
    symbols_queue->push_lexem( plus );
    symbols_queue->push_lexem( a_terminal );
    symbols_queue->push_lexem( round_right );
    symbols_queue->push_lexem( andd );
    symbols_queue->push_lexem( a_terminal );
    symbols_queue->push_lexem( e );
    auto expected = std::vector< int >{ 1, 4, 7, 1, 4, 8, 6, 2, 4, 8, 6, 3, 5, 8, 6, 3 };

    analyser = std::make_shared< LL1Analyser >( symbols_queue, dummy_output, grammar );
    analyser->process( );

    std::cout << string_stream->str( );

    auto result = analyser->get_result( );
    std::vector< int > actual_ids = { };
    for (auto rule : result) {
        actual_ids.push_back( rule->id());
    }

    ASSERT_EQ( actual_ids, expected );
    ASSERT_TRUE( analyser->successfully_parsed() );
}
