#include "Terminal.hpp"

Terminal::Terminal( )
    : Symbol{ true }
{
}

Terminal::Terminal( TerminalGroup group, TerminalSubgroup subgroup )
    : Symbol{ true }
    , type{ group, subgroup }
{
}

bool
Terminal::is_valid( ) const
{
    return type.group != TerminalGroup::INVALID && type.sub_group != TerminalSubgroup::INVALID;
}

bool
Terminal::operator==( const Terminal& other ) const
{
    return type == other.type;
}
