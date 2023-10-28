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

        decimal_terminal = grammar->define( TerminalGroup::NUMERIC, TerminalSubgroup::DECIMAL );
        hex_terminal = grammar->define( TerminalGroup::NUMERIC, TerminalSubgroup::HEX );
        float_terminal = grammar->define( TerminalGroup::NUMERIC, TerminalSubgroup::FLOAT );

        for_terminal = grammar->define( TerminalGroup::RESERVED, TerminalSubgroup::FOR );
        if_terminal = grammar->define( TerminalGroup::RESERVED, TerminalSubgroup::IF );
        return_terminal = grammar->define( TerminalGroup::RESERVED, TerminalSubgroup::RETURN );

        equal_terminal = grammar->define( TerminalGroup::OPERATOR, TerminalSubgroup::EQUAL );
        not_equal_terminal =
                grammar->define( TerminalGroup::OPERATOR, TerminalSubgroup::NOT_EQUAL );
        less_equal_terminal =
                grammar->define( TerminalGroup::OPERATOR, TerminalSubgroup::LESS_EQUAL );

        colon_terminal = grammar->define( TerminalGroup::OTHER, TerminalSubgroup::COLON );
        new_line_terminal = grammar->define( TerminalGroup::OTHER, TerminalSubgroup::NEW_LINE );
        identifier_terminal = grammar->define( TerminalGroup::OTHER, TerminalSubgroup::IDENTIFIER );

        grammar->add_rule( non_terminal, decimal_terminal, hex_terminal, float_terminal );
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

    NonTerminal non_terminal;

    Terminal decimal_terminal, hex_terminal, float_terminal;
    Terminal for_terminal, if_terminal, return_terminal;
    Terminal equal_terminal, not_equal_terminal, less_equal_terminal;
    Terminal colon_terminal, new_line_terminal, identifier_terminal;
};

TEST_F( LexerTest, NumberParsing )
{
    ( *input_string ) << "123 0xf42 12.1231 123ds";

    lexer->process( );

    EXPECT_EQ( lexer->successfully_parsed( ), false );
    ASSERT_EQ( queue->size( ), 4 );
    EXPECT_EQ( queue->pop_lexem( ), decimal_terminal );
    EXPECT_EQ( queue->pop_lexem( ), hex_terminal );
    EXPECT_EQ( queue->pop_lexem( ), float_terminal );
    EXPECT_EQ( queue->pop_lexem( ), Terminal::INVALID_TERMINAL );
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

TEST_F( LexerTest, OperatorParsing )
{
    ( *input_string ) << "== != <=";

    lexer->process( );

    EXPECT_EQ( lexer->successfully_parsed( ), true );
    ASSERT_EQ( queue->size( ), 3 );
    EXPECT_EQ( queue->pop_lexem( ), equal_terminal );
    EXPECT_EQ( queue->pop_lexem( ), not_equal_terminal );
    EXPECT_EQ( queue->pop_lexem( ), less_equal_terminal );
}
