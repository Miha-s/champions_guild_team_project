#ifndef TERMINAL_HPP
#define TERMINAL_HPP
#include <unordered_set>
#include <vector>
#include <unordered_map>

#include "Symbol.hpp"
#include "SymbolType.hpp"
#include "structures/Set.hpp"

enum class TerminalGroup : SymbolId;

enum class TerminalSubgroup : SymbolId;

class Terminal : public Symbol
{
public:
    using Type = SymbolType< TerminalGroup, TerminalSubgroup >;
private:
    const Type m_type;
public:

    Terminal( );

    Type type( ) const;

    bool is_terminal( ) const override;

    TerminalGroup group( ) const;

    TerminalSubgroup subgroup( ) const;

    StringType to_string( ) const override;

    bool is_valid( ) const;

    bool operator==( const Terminal& other ) const;

    static std::shared_ptr< const Terminal > InvalidTerminal( );

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

#define EXPAND_VALUES_TERMINAL_GROUP(action) \
    action(INVALID) \
    action(OTHER) \
    action(NUMERIC) \
    action(RESERVED) \
    action(OPERATOR) \
    action(BRACKET) \
    action(COMMENT)

#define EXPAND_VALUES_TERMINAL_SUBGROUP(action) \
    action(INVALID) \
    action(EPSILON) \
    action(DECIMAL) \
    action(FLOAT) \
    action(HEX) \
    action(BREAK) \
    action(DEFAULT) \
    action(FUNC) \
    action(INTERFACE) \
    action(SELECT) \
    action(CASE) \
    action(DEFER) \
    action(GO) \
    action(MAP) \
    action(STRUCT) \
    action(CHAN) \
    action(ELSE) \
    action(GOTO) \
    action(PACKAGE) \
    action(SWITCH) \
    action(CONST) \
    action(FALLTHROUGH) \
    action(IF) \
    action(RANGE) \
    action(TYPE) \
    action(CONTINUE) \
    action(FOR) \
    action(IMPORT) \
    action(RETURN) \
    action(VAR) \
    action(IDENTIFIER) \
    action(STRONG_NOT_EQUAL) \
    action(STRONG_EQUAL) \
    action(INCREMENT) \
    action(DECREMENT) \
    action(ADD_ASSIGN) \
    action(SUB_ASSIGN) \
    action(MUL_ASSIGN) \
    action(DIV_ASSIGN) \
    action(MOD_ASSIGN) \
    action(EXP_ASSIGN) \
    action(GREATER_EQUAL) \
    action(LESS_EQUAL) \
    action(LOGICAL_AND) \
    action(LOGICAL_OR) \
    action(LOGICAL_NOT) \
    action(LEFT_SHIFT) \
    action(RIGHT_SHIFT) \
    action(PLUS) \
    action(MINUS) \
    action(DIVIDE) \
    action(MULTIPLY) \
    action(EXPONENT) \
    action(ASSIGN) \
    action(MODULUS) \
    action(EQUAL) \
    action(NOT_EQUAL) \
    action(GREATER) \
    action(LESS) \
    action(AND) \
    action(OR) \
    action(NOT) \
    action(POINT) \
    action(ARROW) \
    action(NEW_LINE) \
    action(ROUND_LEFT) \
    action(ROUND_RIGHT) \
    action(SQUARE_LEFT) \
    action(SQUARE_RIGHT) \
    action(FIGURE_LEFT) \
    action(FIGURE_RIGHT) \
    action(SINGLE_QUOTE) \
    action(DOUBLE_QUOTE) \
    action(COLON) \
    action(SEMICOLON) \
    action(ONELINE)

enum class TerminalGroup : SymbolId
{
    EXPAND_VALUES_TERMINAL_GROUP( EXPAND_ENUM )
};

enum class TerminalSubgroup : SymbolId
{
    EXPAND_VALUES_TERMINAL_SUBGROUP( EXPAND_ENUM )
};

using TerminalPtr = std::shared_ptr< const Terminal >;
using Terminals = std::vector< TerminalPtr >;

struct TerminalsHash
{
    size_t
    operator( )( const Terminals& terminals ) const
    {
        size_t hash = 0;

        for ( const auto& terminal : terminals )
        {
            hash ^= std::hash< TerminalPtr >{ }( terminal );
        }

        return hash;
    }
};

#endif  // TERMINAL_HPP
