#include "NonTerminal.hpp"

NonTerminal::NonTerminal( NonTerminalType type, SymbolId id )
    : Symbol{ id }
    , m_type{ type }
{
}

NonTerminal::NonTerminal( )
    : Symbol( INVALID_ID )
    , m_type( NonTerminalType::INVALID )
{
}

NonTerminalType
NonTerminal::type( ) const
{
    return m_type;
}

bool
NonTerminal::is_terminal( ) const
{
    return false;
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

std::shared_ptr< const NonTerminal >
NonTerminal::InvalidNonTerminal( )
{
    static std::shared_ptr< const NonTerminal > invalid_non_terminal( new NonTerminal( ) );

    return invalid_non_terminal;
}
