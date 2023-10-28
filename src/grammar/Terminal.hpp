#ifndef TERMINAL_HPP
#define TERMINAL_HPP
#include <vector>

#include "Symbol.hpp"
#include "SymbolType.hpp"
#include "structures/Set.hpp"

enum class TerminalGroup : SymbolId;

enum class TerminalSubgroup : SymbolId;

struct Position {
    size_t row;
    size_t column;
};

class Terminal : public Symbol
{
    using Type = SymbolType< TerminalGroup, TerminalSubgroup > ;
    Type m_type;

public:
    StringType word;
    Position position;

    Terminal( );

    Type type( ) const;

    TerminalGroup group( ) const;

    TerminalSubgroup subgroup( ) const;

    bool is_valid( ) const;

    bool operator==( const Terminal& other ) const;

    static const Terminal INVALID_TERMINAL;

protected:
    Terminal( TerminalGroup group, TerminalSubgroup subgroup, SymbolId id );

    friend class GrammarSymbols;
};

struct TerminalHash
{
    std::size_t
    operator( )( const Terminal& terminal ) const
    {
        return std::hash< std::size_t >( )( static_cast< std::size_t >( terminal.group( ) )
                                            ^ static_cast< std::size_t >( terminal.subgroup( ) ) );
    }
};

enum class TerminalGroup : SymbolId
{
    INVALID,
    OTHER,
    NUMERIC,
    RESERVED,
    OPERATOR,
    BRACKET,
    COMMENT
};

enum class TerminalSubgroup : SymbolId
{
    INVALID,
    DECIMAL,
    FLOAT,
    HEX,
    BREAK,
    DEFAULT,
    FUNC,
    INTERFACE,
    SELECT,
    CASE,
    DEFER,
    GO,
    MAP,
    STRUCT,
    CHAN,
    ELSE,
    GOTO,
    PACKAGE,
    SWITCH,
    CONST,
    FALLTHROUGH,
    IF,
    RANGE,
    TYPE,
    CONTINUE,
    FOR,
    IMPORT,
    RETURN,
    VAR,
    IDENTIFIER,
    STRONG_NOT_EQUAL,
    STRONG_EQUAL,
    INCREMENT,
    DECREMENT,
    ADD_ASSIGN,
    SUB_ASSIGN,
    MUL_ASSIGN,
    DIV_ASSIGN,
    MOD_ASSIGN,
    EXP_ASSIGN,
    GREATER_EQUAL,
    LESS_EQUAL,
    LOGICAL_AND,
    LOGICAL_OR,
    LOGICAL_NOT,
    LEFT_SHIFT,
    RIGHT_SHIFT,
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
    POINT,
    ARROW,
    NEW_LINE,
    ROUND_LEFT,
    ROUND_RIGHT,
    SQUARE_LEFT,
    SQUARE_RIGHT,
    FIGURE_LEFT,
    FIGURE_RIGHT,
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    COLON,
    SEMICOLON,
    ONELINE,
};

using Terminals = std::vector< Terminal >;

#endif  // TERMINAL_HPP
