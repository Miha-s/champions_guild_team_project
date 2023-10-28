#include "FiniteAutomataLexer.hpp"
#include <cassert>
#include <unordered_map>

FiniteAutomataLexer::FiniteAutomataLexer( InputStreamPtr input,
                                          TerminalsQueuePtr queue,
                                          OutputStreamPtr output,
                                          GrammarPtr grammar )
    : Lexer( input, queue, output, grammar )
{
}

bool
is_white_character( int c )
{
    return c != '\n' && std::isspace( c );
}

void
skip_white_characters( InputStreamPtr istream )
{
    while ( is_white_character( istream->peek( ) ) )
    {
        istream->get( );
    }
}

StringType
read_until_lexem_end( InputStreamPtr istream )
{
    StringType res;
    while ( std::isalnum( istream->peek( ) ) )
    {
        res.push_back( istream->get( ) );
    }

    return res;
}

void
FiniteAutomataLexer::process( )
{
    m_success = true;
    auto lexem = read_next_lexem( );
    while ( lexem )
    {
        m_queue->push_lexem( *lexem );
        lexem = read_next_lexem( );
    }
}

bool
FiniteAutomataLexer::successfully_parsed( ) const
{
    return m_success;
}

Lexer::FailedState
FiniteAutomataLexer::get_failed_state( ) const
{
    return FailedState{ };
}

FiniteAutomataLexer::TerminalPtr
FiniteAutomataLexer::read_next_lexem( )
{
    skip_white_characters( m_input );

    int symbol = m_input->peek( );

    if ( symbol == EOF )
    {
        return { };
    }

    auto position = m_input->get_position( );

    Terminal lexem = Terminal::INVALID_TERMINAL;

    if ( isalpha( symbol ) || symbol == '_' )
    {
        lexem = read_letter_lexem( );
    }
    else if ( std::isdigit( symbol ) )
    {
        lexem = read_number_lexem( );
    }
    else
    {
        lexem = read_operator_lexem( );
    }

    lexem.position = { position.first, position.second };

    if ( lexem == Terminal::INVALID_TERMINAL )
    {
        lexem.word.append( read_until_lexem_end( m_input ) );
        m_success = false;
    }

    return std::make_shared< Terminal >( lexem );
}

enum class Num
{
    INITIAL,
    MAYBE_HEX_OR_FLOAT,
    HEX_PREFIX,
    DECIMAL,
    HEX,
    FLOAT,
    FINISH_STATES,
    F_DECIMAL,
    F_HEX,
    F_FLOAT,
    F_FAILED
};

Num
get_next_number_state( Num state, int c )
{
    switch ( state )
    {
    case Num::INITIAL:
        if ( c == '0' )
        {
            state = Num::MAYBE_HEX_OR_FLOAT;
        }
        else if ( isdigit( c ) )
        {
            state = Num::DECIMAL;
        }
        else
        {
            state = Num::F_FAILED;
        }
        break;
    case Num::MAYBE_HEX_OR_FLOAT:
        if ( c == 'x' || c == 'X' )
        {
            state = Num::HEX_PREFIX;
        }
        else if ( c == '.' )
        {
            state = Num::FLOAT;
        }
        else if ( !isalpha( c ) )
        {
            state = Num::F_DECIMAL;
        }
        else
        {
            state = Num::F_FAILED;
        }
        break;
    case Num::DECIMAL:
        if ( isdigit( c ) )
        {
            break;
        }
        if ( c == '.' )
        {
            state = Num::FLOAT;
        }
        else if ( !isalpha( c ) )
        {
            state = Num::F_DECIMAL;
        }
        else
        {
            state = Num::F_FAILED;
        }
        break;
    case Num::FLOAT:
        if ( isdigit( c ) )
        {
            break;
        }
        if ( !isalpha( c ) )
        {
            state = Num::F_FLOAT;
        }
        else
        {
            state = Num::F_FAILED;
        }
        break;
    case Num::HEX_PREFIX:
        if ( c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'A'
             || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F' || isdigit( c ) )
        {
            state = Num::HEX;
            break;
        }
        state = Num::F_FAILED;
        break;
    case Num::HEX:
        if ( c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'A'
             || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F' || isdigit( c ) )
        {
            break;
        }
        if ( !isalpha( c ) )
        {
            state = Num::F_HEX;
        }
        else
        {
            state = Num::F_FAILED;
        }
        break;
    default:
        return Num::F_FAILED;
    }

    return state;
}

Terminal
FiniteAutomataLexer::read_number_lexem( )
{
    int c;
    Num state = Num::INITIAL;
    StringType value;

    while ( true )
    {
        c = m_input->peek( );

        state = get_next_number_state( state, c );

        if ( state > Num::FINISH_STATES )
        {
            break;
        }

        value.push_back( c );
        m_input->get( );
    }

    auto output = Terminal::INVALID_TERMINAL;
    if ( state == Num::F_HEX )
    {
        output = m_grammar->create( TerminalGroup::NUMERIC, TerminalSubgroup::HEX );
    }
    else if ( state == Num::F_DECIMAL )
    {
        output = m_grammar->create( TerminalGroup::NUMERIC, TerminalSubgroup::DECIMAL );
    }
    else if ( state == Num::F_FLOAT )
    {
        output = m_grammar->create( TerminalGroup::NUMERIC, TerminalSubgroup::FLOAT );
    }

    output.word = value;

    return output;
}

static const std::unordered_map< StringType, TerminalSubgroup > ReservedLiteralsMap = {
    { "break", TerminalSubgroup::BREAK },
    { "default", TerminalSubgroup::DEFAULT },
    { "func", TerminalSubgroup::FUNC },
    { "interface", TerminalSubgroup::INTERFACE },
    { "select", TerminalSubgroup::SELECT },
    { "case", TerminalSubgroup::CASE },
    { "defer", TerminalSubgroup::DEFER },
    { "go", TerminalSubgroup::GO },
    { "map", TerminalSubgroup::MAP },
    { "struct", TerminalSubgroup::STRUCT },
    { "chan", TerminalSubgroup::CHAN },
    { "else", TerminalSubgroup::ELSE },
    { "goto", TerminalSubgroup::GOTO },
    { "package", TerminalSubgroup::PACKAGE },
    { "switch", TerminalSubgroup::SWITCH },
    { "const", TerminalSubgroup::CONST },
    { "fallthrough", TerminalSubgroup::FALLTHROUGH },
    { "if", TerminalSubgroup::IF },
    { "range", TerminalSubgroup::RANGE },
    { "type", TerminalSubgroup::TYPE },
    { "continue", TerminalSubgroup::CONTINUE },
    { "for", TerminalSubgroup::FOR },
    { "import", TerminalSubgroup::IMPORT },
    { "return", TerminalSubgroup::RETURN },
    { "var", TerminalSubgroup::VAR }
};

int
accepted_letter( char c )
{
    return isalpha( c ) || isdigit( c ) || c == '_';
}

Terminal
FiniteAutomataLexer::read_letter_lexem( )
{
    StringType value;
    while ( accepted_letter( m_input->peek( ) ) )
    {
        value.push_back( m_input->get( ) );
    }

    auto it = ReservedLiteralsMap.find( value );
    auto output = Terminal::INVALID_TERMINAL;

    if ( it != ReservedLiteralsMap.end( ) )
    {
        output = m_grammar->create( TerminalGroup::RESERVED, it->second );
    }
    else
    {
        output = m_grammar->create( TerminalGroup::OTHER, TerminalSubgroup::IDENTIFIER );
    }

    output.word = value;

    return output;
}


enum class Sym {
    INITIAL,
    PLUS,
    MINUS,
    DIVIDE,
    MULTIPLY,
    EXPONENT,
    ASSIGN,
    MODULUS,
    EQUAL,
    NOT_EQUAL,
    GREATER,
    LESS,
    AND,
    OR,
    NOT,
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    ONE_LINE_COMMENT,
    EMPTY,
    FINISH_STATES,
    F_STRONG_NOT_EQUAL,
    F_STRONG_EQUAL,
    F_INCREMENT,
    F_DECREMENT,
    F_ADD_ASSIGN,
    F_SUB_ASSIGN,
    F_MUL_ASSIGN,
    F_DIV_ASSIGN,
    F_MOD_ASSIGN,
    F_EXP_ASSIGN,
    F_GREATER_EQUAL,
    F_LESS_EQUAL,
    F_TERNARY,
    F_LOGICAL_AND,
    F_LOGICAL_OR,
    F_LEFT_SHIFT,
    F_RIGHT_SHIFT,
    F_PLUS,
    F_MINUS,
    F_DIVIDE,
    F_MULTIPLY,
    F_EXPONENT,
    F_ASSIGN,
    F_MODULUS,
    F_EQUAL,
    F_NOT_EQUAL,
    F_GREATER,
    F_LESS,
    F_AND,
    F_OR,
    F_NOT,
    F_POINT,
    F_ARROW,
    F_NEW_LINE,
    F_ROUND_LEFT_BRACKET,
    F_ROUND_RIGHT_BRACKET,
    F_SQUARE_LEFT_BRACKET,
    F_SQUARE_RIGHT_BRACKET,
    F_FIGURE_LEFT_BRACKET,
    F_FIGURE_RIGHT_BRACKET,
    F_SINGLE_STRING_LITERAL,
    F_DOUBLE_STRING_LITERAL,
    F_COLON,
    F_SEMICOLON,
    F_ONELINE_COMMENT,
    F_FAILED,
};

static const std::unordered_map< char, Sym > SymbolEnumMap = { { '+', Sym::PLUS },
                                                               { '-', Sym::MINUS },
                                                               { '/', Sym::DIVIDE },
                                                               { '*', Sym::MULTIPLY },
                                                               { '=', Sym::ASSIGN },
                                                               { '%', Sym::MODULUS },
                                                               { '>', Sym::GREATER },
                                                               { '<', Sym::LESS },
                                                               { '&', Sym::AND },
                                                               { '|', Sym::OR },
                                                               { '!', Sym::NOT },
                                                               { '.', Sym::F_POINT },
                                                               { '\n', Sym::F_NEW_LINE },
                                                               { '(', Sym::F_ROUND_LEFT_BRACKET },
                                                               { ')', Sym::F_ROUND_RIGHT_BRACKET },
                                                               { '[', Sym::F_SQUARE_LEFT_BRACKET },
                                                               { ']', Sym::F_SQUARE_RIGHT_BRACKET },
                                                               { '{', Sym::F_FIGURE_LEFT_BRACKET },
                                                               { '}', Sym::F_FIGURE_RIGHT_BRACKET },
                                                               { '\'', Sym::SINGLE_QUOTE },
                                                               { '"', Sym::DOUBLE_QUOTE },
                                                               { ':', Sym::F_COLON },
                                                               { ';', Sym::F_SEMICOLON } };

static const std::unordered_map< Sym, std::pair< TerminalGroup, TerminalSubgroup > >
        FinishTerminalMap = {
            { Sym::F_STRONG_NOT_EQUAL,
              { TerminalGroup::OPERATOR, TerminalSubgroup::STRONG_NOT_EQUAL } },
            { Sym::F_STRONG_EQUAL, { TerminalGroup::OPERATOR, TerminalSubgroup::STRONG_EQUAL } },
            { Sym::F_INCREMENT, { TerminalGroup::OPERATOR, TerminalSubgroup::INCREMENT } },
            { Sym::F_DECREMENT, { TerminalGroup::OPERATOR, TerminalSubgroup::DECREMENT } },
            { Sym::F_ADD_ASSIGN, { TerminalGroup::OPERATOR, TerminalSubgroup::ADD_ASSIGN } },
            { Sym::F_SUB_ASSIGN, { TerminalGroup::OPERATOR, TerminalSubgroup::SUB_ASSIGN } },
            { Sym::F_MUL_ASSIGN, { TerminalGroup::OPERATOR, TerminalSubgroup::MUL_ASSIGN } },
            { Sym::F_DIV_ASSIGN, { TerminalGroup::OPERATOR, TerminalSubgroup::DIV_ASSIGN } },
            { Sym::F_MOD_ASSIGN, { TerminalGroup::OPERATOR, TerminalSubgroup::MOD_ASSIGN } },
            { Sym::F_EXP_ASSIGN, { TerminalGroup::OPERATOR, TerminalSubgroup::EXP_ASSIGN } },
            { Sym::F_GREATER_EQUAL, { TerminalGroup::OPERATOR, TerminalSubgroup::GREATER_EQUAL } },
            { Sym::F_LESS_EQUAL, { TerminalGroup::OPERATOR, TerminalSubgroup::LESS_EQUAL } },
            { Sym::F_LOGICAL_AND, { TerminalGroup::OPERATOR, TerminalSubgroup::LOGICAL_AND } },
            { Sym::F_LOGICAL_OR, { TerminalGroup::OPERATOR, TerminalSubgroup::LOGICAL_OR } },
            { Sym::F_LEFT_SHIFT, { TerminalGroup::OPERATOR, TerminalSubgroup::LEFT_SHIFT } },
            { Sym::F_RIGHT_SHIFT, { TerminalGroup::OPERATOR, TerminalSubgroup::RIGHT_SHIFT } },
            { Sym::F_PLUS, { TerminalGroup::OPERATOR, TerminalSubgroup::PLUS } },
            { Sym::F_MINUS, { TerminalGroup::OPERATOR, TerminalSubgroup::MINUS } },
            { Sym::F_DIVIDE, { TerminalGroup::OPERATOR, TerminalSubgroup::DIVIDE } },
            { Sym::F_MULTIPLY, { TerminalGroup::OPERATOR, TerminalSubgroup::MULTIPLY } },
            { Sym::F_EXPONENT, { TerminalGroup::OPERATOR, TerminalSubgroup::EXPONENT } },
            { Sym::F_ASSIGN, { TerminalGroup::OPERATOR, TerminalSubgroup::ASSIGN } },
            { Sym::F_MODULUS, { TerminalGroup::OPERATOR, TerminalSubgroup::MODULUS } },
            { Sym::F_EQUAL, { TerminalGroup::OPERATOR, TerminalSubgroup::EQUAL } },
            { Sym::F_NOT_EQUAL, { TerminalGroup::OPERATOR, TerminalSubgroup::NOT_EQUAL } },
            { Sym::F_GREATER, { TerminalGroup::OPERATOR, TerminalSubgroup::GREATER } },
            { Sym::F_LESS, { TerminalGroup::OPERATOR, TerminalSubgroup::LESS } },
            { Sym::F_AND, { TerminalGroup::OPERATOR, TerminalSubgroup::AND } },
            { Sym::F_OR, { TerminalGroup::OPERATOR, TerminalSubgroup::OR } },
            { Sym::F_NOT, { TerminalGroup::OPERATOR, TerminalSubgroup::NOT } },
            { Sym::F_FAILED, { TerminalGroup::INVALID, TerminalSubgroup::INVALID } },
            { Sym::F_POINT, { TerminalGroup::OPERATOR, TerminalSubgroup::POINT } },
            { Sym::F_ARROW, { TerminalGroup::OPERATOR, TerminalSubgroup::ARROW } },
            { Sym::F_NEW_LINE, { TerminalGroup::OPERATOR, TerminalSubgroup::NEW_LINE } },
            { Sym::F_ROUND_LEFT_BRACKET,
              { TerminalGroup::OPERATOR, TerminalSubgroup::ROUND_LEFT } },
            { Sym::F_ROUND_RIGHT_BRACKET,
              { TerminalGroup::OPERATOR, TerminalSubgroup::ROUND_RIGHT } },
            { Sym::F_SQUARE_LEFT_BRACKET,
              { TerminalGroup::OPERATOR, TerminalSubgroup::SQUARE_LEFT } },
            { Sym::F_SQUARE_RIGHT_BRACKET,
              { TerminalGroup::OPERATOR, TerminalSubgroup::SQUARE_RIGHT } },
            { Sym::F_FIGURE_LEFT_BRACKET,
              { TerminalGroup::OPERATOR, TerminalSubgroup::FIGURE_LEFT } },
            { Sym::F_FIGURE_RIGHT_BRACKET,
              { TerminalGroup::OPERATOR, TerminalSubgroup::FIGURE_RIGHT } },
            { Sym::F_SINGLE_STRING_LITERAL,
              { TerminalGroup::OPERATOR, TerminalSubgroup::SINGLE_QUOTE } },
            { Sym::F_DOUBLE_STRING_LITERAL,
              { TerminalGroup::OPERATOR, TerminalSubgroup::DOUBLE_QUOTE } },
            { Sym::F_COLON, { TerminalGroup::OPERATOR, TerminalSubgroup::COLON } },
            { Sym::F_SEMICOLON, { TerminalGroup::OPERATOR, TerminalSubgroup::SEMICOLON } },
            { Sym::F_ONELINE_COMMENT, { TerminalGroup::OPERATOR, TerminalSubgroup::ONELINE } }
        };

#define ADVANCE value.push_back(m_input->get( ))

Terminal
FiniteAutomataLexer::read_operator_lexem( )
{
    int c;
    Sym state = Sym::INITIAL;
    Sym tmp_state = Sym::INITIAL;
    StringType value;

    while ( true )
    {
        c = m_input->peek( );
        auto it = SymbolEnumMap.find( c );

        if ( it != SymbolEnumMap.end( ) )
        {
            tmp_state = it->second;
        }
        else
        {
            tmp_state = Sym::EMPTY;
        }

        if ( c == EOF )
        {
            tmp_state = Sym::EMPTY;
        }

        switch (state)
        {
        case Sym::INITIAL:
            state = tmp_state;

            switch (state)
            {
            case Sym::F_POINT:
            case Sym::F_NEW_LINE:
            case Sym::F_ROUND_LEFT_BRACKET:
            case Sym::F_ROUND_RIGHT_BRACKET:
            case Sym::F_SQUARE_LEFT_BRACKET:
            case Sym::F_SQUARE_RIGHT_BRACKET:
            case Sym::F_FIGURE_LEFT_BRACKET:
            case Sym::F_FIGURE_RIGHT_BRACKET:
            case Sym::F_COLON:
            case Sym::F_SEMICOLON:
                ADVANCE;
            default:
                void( );
            }

            if(tmp_state == Sym::EMPTY) {
                state = Sym::F_FAILED;
            }

            break;
        case Sym::PLUS:
            switch (tmp_state) {
            case Sym::PLUS: state = Sym::F_INCREMENT; ADVANCE; break;
            case Sym::ASSIGN: state = Sym::F_ADD_ASSIGN; ADVANCE; break;
            default: state = Sym::F_PLUS; break; }
            break;
        case Sym::MINUS:
            switch (tmp_state) {
            case Sym::MINUS: state = Sym::F_DECREMENT; ADVANCE; break;
            case Sym::ASSIGN: state = Sym::F_SUB_ASSIGN; ADVANCE; break;
            case Sym::GREATER: state = Sym::F_ARROW; ADVANCE; break;
            default: state = Sym::F_MINUS; break; }
            break;
        case Sym::DIVIDE:
            switch (tmp_state) {
            case Sym::ASSIGN: state = Sym::F_DIV_ASSIGN; ADVANCE; break;
            case Sym::DIVIDE: state = Sym::ONE_LINE_COMMENT; break;
            default: state = Sym::F_DIVIDE; break; }
            break;
        case Sym::MULTIPLY:
            switch (tmp_state) {
            case Sym::ASSIGN: state = Sym::F_MUL_ASSIGN; ADVANCE; break;
            case Sym::MULTIPLY: state = Sym::EXPONENT; break;
            default: state = Sym::F_MULTIPLY; break; }
            break;
        case Sym::EXPONENT:
            switch (tmp_state) {
            case Sym::ASSIGN: state = Sym::F_EXP_ASSIGN; ADVANCE; break;
            default: state = Sym::F_EXPONENT; break; }
            break;
        case Sym::MODULUS:
            switch (tmp_state) {
            case Sym::ASSIGN: state = Sym::F_MOD_ASSIGN; ADVANCE; break;
            default: state = Sym::F_MODULUS; break; }
            break;
        case Sym::ASSIGN:
            switch (tmp_state) {
            case Sym::ASSIGN: state = Sym::EQUAL; break;
            default: state = Sym::F_ASSIGN; break; }
            break;
        case Sym::EQUAL:
            switch (tmp_state) {
            case Sym::ASSIGN: state = Sym::F_STRONG_EQUAL; ADVANCE; break;
            default: state = Sym::F_EQUAL; break; }
            break;
        case Sym::NOT:
            switch (tmp_state) {
            case Sym::ASSIGN: state = Sym::NOT_EQUAL; break;
            default: state = Sym::F_NOT; break; }
            break;
        case Sym::NOT_EQUAL:
            switch (tmp_state) {
            case Sym::ASSIGN: state = Sym::F_STRONG_NOT_EQUAL; ADVANCE; break;
            default: state = Sym::F_NOT_EQUAL; break; }
            break;
        case Sym::GREATER:
            switch (tmp_state) {
            case Sym::ASSIGN: state = Sym::F_GREATER_EQUAL; ADVANCE; break;
            case Sym::GREATER: state = Sym::F_RIGHT_SHIFT; ADVANCE; break;
            default: state = Sym::F_GREATER; break; }
            break;
        case Sym::LESS:
            switch (tmp_state) {
            case Sym::ASSIGN: state = Sym::F_LESS_EQUAL; ADVANCE; break;
            case Sym::LESS: state = Sym::F_LEFT_SHIFT; ADVANCE; break;
            default: state = Sym::F_LESS; break; }
            break;
        case Sym::AND:
            switch (tmp_state) {
            case Sym::AND: state = Sym::F_LOGICAL_AND; ADVANCE; break;
            default: state = Sym::F_AND; break; }
            break;
        case Sym::OR:
            switch (tmp_state) {
            case Sym::OR: state = Sym::F_LOGICAL_OR; ADVANCE; break;
            default: state = Sym::F_OR; break; }
            break;
        case Sym::SINGLE_QUOTE:
            switch (tmp_state) {
            case Sym::SINGLE_QUOTE: state = Sym::F_SINGLE_STRING_LITERAL; ADVANCE; break;
            case Sym::F_NEW_LINE: state = Sym::F_FAILED; break;
            default: state = Sym::SINGLE_QUOTE; break; }
            break;
        case Sym::DOUBLE_QUOTE:
            switch (tmp_state) {
            case Sym::DOUBLE_QUOTE: state = Sym::F_DOUBLE_STRING_LITERAL; ADVANCE; break;
            case Sym::F_NEW_LINE: state = Sym::F_FAILED; break;
            default: state = Sym::DOUBLE_QUOTE; break; }
            break;
        case Sym::ONE_LINE_COMMENT:
            switch (tmp_state) {
            case Sym::F_NEW_LINE: state = Sym::F_ONELINE_COMMENT; break;
            default: state = Sym::ONE_LINE_COMMENT; break; }
            break;
        default:
            assert( false );
        }

        if(state > Sym::FINISH_STATES) {
            break;
        }
        ADVANCE;
    }

    auto result = FinishTerminalMap.at( state );
    if ( result.first == TerminalGroup::INVALID )
    {
        return Terminal::INVALID_TERMINAL;
    }

    auto lexem = m_grammar->create( result.first, result.second );
    lexem.word = value;

    return lexem;
}
