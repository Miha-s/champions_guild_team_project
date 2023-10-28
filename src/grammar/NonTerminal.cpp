#include "NonTerminal.hpp"

NonTerminal::NonTerminal( )
    : Symbol{ false }
{
}

NonTerminal::NonTerminal( NonTerminalGroup group, NonTerminalSubgroup subgroup )
    : Symbol{ false }
    , type{ group, subgroup }
{
}

bool
NonTerminal::is_valid( ) const
{
    return type.group != NonTerminalGroup::INVALID
           && type.sub_group != NonTerminalSubgroup::INVALID;
};

bool
NonTerminal::operator==( const NonTerminal& other ) const
{
    return type == other.type;
}
