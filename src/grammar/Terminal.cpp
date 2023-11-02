#include "Terminal.hpp"

Terminal const Terminal::INVALID_TERMINAL = { TerminalGroup::INVALID,
                                              TerminalSubgroup::INVALID,
                                              INVALID_ID };

Terminal const Terminal::EPSILON_TERMINAL = { TerminalGroup::OTHER,
                                              TerminalSubgroup::EPSILON,
                                              EPSILON_ID };

Terminal::Terminal( TerminalGroup group, TerminalSubgroup subgroup, SymbolId id )
    : Symbol{ true, id }
    , m_type{ group, subgroup }
{
}

Terminal::Terminal( )
    : Symbol( INVALID_TERMINAL )
{
    *this = INVALID_TERMINAL;
}

Terminal::Type
Terminal::type( ) const
{
    return m_type;
}

TerminalGroup
Terminal::group( ) const
{
    return m_type.group;
}

TerminalSubgroup
Terminal::subgroup( ) const
{
    return m_type.sub_group;
}

bool
Terminal::is_valid( ) const
{
    return m_type.group != TerminalGroup::INVALID && m_type.sub_group != TerminalSubgroup::INVALID
           && Symbol::is_valid( );
}

bool
Terminal::operator==( const Terminal& other ) const
{
    return m_type == other.m_type && Symbol::operator==( other );
}
