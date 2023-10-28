#include <gtest/gtest.h>

#include <lexer/FiniteAutomataLexer.hpp>
#include <sstream>

class LexerTest : public testing::Test
{
protected:
    void
    SetUp( ) override
    {
        input_string = std::make_shared< std::stringstream >( );
        InputStream inp{ std::static_pointer_cast< std::istream >( input_string ) };
        input = std::make_shared< InputStream >( inp );

        queue = std::make_shared< TerminalsQueue >( );

        auto dummy_output_stream = std::make_shared< std::ostringstream >( );
        dummy_output = std::static_pointer_cast< std::ostream >( dummy_output_stream );

        grammar = std::make_shared< Grammar >( );
        grammar->add_rule( non_terminal, decimal_terminal, hex_teminal, float_terminal );
        grammar->add_rule( non_terminal, for_terminal, if_terminal, return_terminal );
        grammar->add_rule( non_terminal, equal_terminal, not_equal_terminal, less_equal_terminal );
        grammar->add_rule( non_terminal, colon_terminal, new_line_terminal, identifier_terminal );

        lexer = std::make_shared< FiniteAutomataLexer >( input, queue, dummy_output, grammar );
    }

    std::shared_ptr< std::stringstream > input_string;
    InputStreamPtr input;
    OutputStreamPtr dummy_output;
    TerminalsQueuePtr queue;
    GrammarPtr grammar;

    std::shared_ptr< Lexer > lexer;

    NonTerminal non_terminal = INVALID_NON_TERMINAL;

    Terminal decimal_terminal{ TerminalGroup::NUMERIC, TerminalSubgroup::DECIMAL };
    Terminal hex_teminal{ TerminalGroup::NUMERIC, TerminalSubgroup::HEX };
    Terminal float_terminal{ TerminalGroup::NUMERIC, TerminalSubgroup::FLOAT };

    Terminal for_terminal{ TerminalGroup::RESERVED, TerminalSubgroup::FOR };
    Terminal if_terminal{ TerminalGroup::RESERVED, TerminalSubgroup::IF };
    Terminal return_terminal{ TerminalGroup::RESERVED, TerminalSubgroup::RETURN };

    Terminal equal_terminal{ TerminalGroup::OPERATOR, TerminalSubgroup::EQUAL };
    Terminal not_equal_terminal{ TerminalGroup::OPERATOR, TerminalSubgroup::NOT_EQUAL };
    Terminal less_equal_terminal{ TerminalGroup::OPERATOR, TerminalSubgroup::LESS_EQUAL };

    Terminal colon_terminal{ TerminalGroup::OTHER, TerminalSubgroup::COLON };
    Terminal new_line_terminal{ TerminalGroup::OTHER, TerminalSubgroup::NEW_LINE };
    Terminal identifier_terminal{ TerminalGroup::OTHER, TerminalSubgroup::IDENTIFIER };
};

TEST_F( LexerTest, NumberParsing )
{
    ( *input_string ) << "123 0xf42 12.1231 123ds";

    lexer->process( );

    EXPECT_EQ( lexer->successfully_parsed( ), false );
    ASSERT_EQ( queue->size( ), 4 );
    EXPECT_EQ( queue->pop_lexem( ), decimal_terminal );
    EXPECT_EQ( queue->pop_lexem( ), hex_teminal );
    EXPECT_EQ( queue->pop_lexem( ), float_terminal );
    EXPECT_EQ( queue->pop_lexem( ), INVALID_TERMINAL );
}

TEST_F( LexerTest, StringParsing )
{
    ( *input_string ) << "for if return";

    lexer->process( );

    EXPECT_EQ( lexer->successfully_parsed( ), true );
    ASSERT_EQ( queue->size( ), 3 );
    EXPECT_EQ( queue->pop_lexem( ), for_terminal );
    EXPECT_EQ( queue->pop_lexem( ), if_terminal );
    EXPECT_EQ( queue->pop_lexem( ), return_terminal );
}

TEST_F(LexerTest, OperatorParsing)
{
    ( *input_string ) << "== != <=";

    lexer->process( );

    EXPECT_EQ( lexer->successfully_parsed( ), true );
    ASSERT_EQ( queue->size( ), 3 );
    EXPECT_EQ( queue->pop_lexem( ), equal_terminal );
    EXPECT_EQ( queue->pop_lexem( ), not_equal_terminal );
    EXPECT_EQ( queue->pop_lexem( ), less_equal_terminal );
}
