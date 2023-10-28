#include "NonTerminal.hpp"

NonTerminal::NonTerminal( )
    : Symbol{ false }
{
}

NonTerminal::NonTerminal( NonTerminalType group )
    : Symbol{ false }
    , type{ group }
{
}

bool
NonTerminal::is_valid( ) const
{
    return type != NonTerminalType::INVALID;
};

bool
NonTerminal::operator==( const NonTerminal& other ) const
{
    return type == other.type;
}
