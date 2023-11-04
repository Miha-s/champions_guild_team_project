#include <gtest/gtest.h>

#include <lexer/FiniteAutomataLexer.hpp>

#include "algorithms/algorithms.hpp"

class LL1Test : public testing::Test
{
protected:
    void
    SetUp( ) override
    {
        grammar = std::make_shared< Grammar >( );
    }

    GrammarPtr grammar;
};

TEST_F( LL1Test, Test )
{

}


