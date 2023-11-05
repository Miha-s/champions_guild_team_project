#include "Terminal.hpp"

#define EXPAND_ENUM_TERMINAL_GROUP_STRING_MAP(token) EXPAND_ENUM_STRING_MAP(token, TerminalGroup)
static std::unordered_map< TerminalGroup, StringType > TerminalGroupStringMap = {
    EXPAND_VALUES_TERMINAL_GROUP( EXPAND_ENUM_TERMINAL_GROUP_STRING_MAP )
};
#undef EXPAND_ENUM_TERMINAL_GROUP_STRING_MAP

#define EXPAND_ENUM_TERMINAL_SUBGROUP_STRING_MAP(token) EXPAND_ENUM_STRING_MAP(token, TerminalSubgroup)
static std::unordered_map< TerminalSubgroup, StringType > TerminalSubgroupStringMap = {
    EXPAND_VALUES_TERMINAL_SUBGROUP( EXPAND_ENUM_TERMINAL_SUBGROUP_STRING_MAP )
};
#undef EXPAND_ENUM_TERMINAL_SUBGROUP_STRING_MAP

Terminal::Terminal( TerminalGroup group, TerminalSubgroup subgroup, SymbolId id )
    : Symbol{ id }
    , m_type{ group, subgroup }
{
}

Terminal::Terminal( )
    : Symbol( INVALID_ID )
    , m_type( { TerminalGroup::INVALID, TerminalSubgroup::INVALID } )
{
}

Terminal::Type
Terminal::type( ) const
{
    return m_type;
}

bool
Terminal::is_terminal( ) const
{
    return true;
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

StringType
Terminal::to_string( ) const
{
    StringType str;
    str = TerminalGroupStringMap[ group( ) ];
    str.push_back( '_' );
    str.append( TerminalSubgroupStringMap[ subgroup( ) ] );
    return str;
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

std::shared_ptr< const Terminal >
Terminal::InvalidTerminal( )
{
    static std::shared_ptr< const Terminal > invalid_terminal;
    return invalid_terminal;
}
