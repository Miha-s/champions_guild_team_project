#include "NonTerminal.hpp"

const NonTerminal NonTerminal::INVALID_NON_TERMINAL = { NonTerminalType::INVALID, INVALID_ID };

NonTerminal::NonTerminal( NonTerminalType type, SymbolId id )
    : Symbol{ false, id }
    , m_type{ type }
{
}

NonTerminal::NonTerminal( )
    : Symbol( INVALID_NON_TERMINAL )
{
    *this = INVALID_NON_TERMINAL;
}

NonTerminalType
NonTerminal::type( ) const
{
    return m_type;
}

bool
NonTerminal::is_valid( ) const
{
    return m_type != NonTerminalType::INVALID;
};

bool
NonTerminal::operator==( const NonTerminal& other ) const
{
    return m_type == other.m_type && Symbol::operator==( other );
}
