#include <gtest/gtest.h>

#include <lexer/FiniteAutomataLexer.hpp>
#include <sstream>

#include "algorithms/algorithms.hpp"

class AlgoTest : public testing::Test
{
protected:
    void
    SetUp( ) override
    {
        grammar = std::make_shared< Grammar >( );
    }

    GrammarPtr grammar;
};

TEST_F( AlgoTest, FUCKING_FIRST_2_TEST )
{
    auto e = grammar->epsilon( );
    auto plus = grammar->define( TerminalGroup::OTHER, TerminalSubgroup::PLUS );
    auto andd = grammar->define( TerminalGroup::OTHER, TerminalSubgroup::AND );
    auto round_left = grammar->define( TerminalGroup::OTHER, TerminalSubgroup::ROUND_LEFT );
    auto round_right = grammar->define( TerminalGroup::OTHER, TerminalSubgroup::ROUND_RIGHT );
    auto a_terminal = grammar->define( TerminalGroup::COMMENT, TerminalSubgroup::VAR );

    auto a = grammar->define( NonTerminalType::A );
    auto b = grammar->define( NonTerminalType::B );
    auto c = grammar->define( NonTerminalType::C );
    auto d = grammar->define( NonTerminalType::D );
    auto s = grammar->define( NonTerminalType::S );
    grammar->add_rule( s, b, a );
    grammar->add_rule( a, plus, b, a );
    grammar->add_rule( a, e );
    grammar->add_rule( c, e );
    grammar->add_rule( d, a_terminal );
    grammar->add_rule( b, d, c );
    grammar->add_rule( c, andd, d, c );
    grammar->add_rule( c, andd, d, c );
    grammar->add_rule( d, round_left, s, round_right );

    auto result = first_k( *grammar, 2 );

    EXPECT_EQ( result[ s ], (TerminalsSet{
                                    Terminals{ a_terminal },
                                    Terminals{ a_terminal, plus },
                                    Terminals{ a_terminal, andd },
                                    Terminals{ round_left, a_terminal },
                                    Terminals{ round_left,round_left } }) );
}

TEST_F( AlgoTest, FUCKING_FOLLOW_1_TEST ) {
    auto e = grammar->epsilon( );
    auto plus = grammar->define( TerminalGroup::OTHER, TerminalSubgroup::PLUS );
    auto andd = grammar->define( TerminalGroup::OTHER, TerminalSubgroup::AND );
    auto round_left = grammar->define( TerminalGroup::OTHER, TerminalSubgroup::ROUND_LEFT );
    auto round_right = grammar->define( TerminalGroup::OTHER, TerminalSubgroup::ROUND_RIGHT );
    auto a_terminal = grammar->define( TerminalGroup::COMMENT, TerminalSubgroup::VAR );

    auto a = grammar->define( NonTerminalType::A );
    auto b = grammar->define( NonTerminalType::B );
    auto c = grammar->define( NonTerminalType::C );
    auto d = grammar->define( NonTerminalType::D );
    auto s = grammar->define( NonTerminalType::S );
    grammar->add_rule( s, b, a );
    grammar->add_rule( a, plus, b, a );
    grammar->add_rule( a, e );
    grammar->add_rule( c, e );
    grammar->add_rule( d, a_terminal );
    grammar->add_rule( b, d, c );
    grammar->add_rule( c, andd, d, c );
    grammar->add_rule( c, andd, d, c );
    grammar->add_rule( d, round_left, s, round_right );

    auto result = follow_k( *grammar, 1 );

    EXPECT_EQ( result[ d ], (TerminalsSet{
                                    Terminals{ andd },
                                    Terminals{ plus },
//                                    Terminals{ e },
                                    Terminals{ round_right }}) );
}
