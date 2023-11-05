#include "NonTerminal.hpp"

#define EXPAND_ENUM_NON_TERMINAL_TYPE_STRING_MAP(token) EXPAND_ENUM_STRING_MAP(token, NonTerminalType)
static std::unordered_map< NonTerminalType, StringType > NonTerminalTypeStringMap = {
    EXPAND_VALUES_NON_TERINAL_TYPE( EXPAND_ENUM_NON_TERMINAL_TYPE_STRING_MAP )
};
#undef EXPAND_ENUM_NON_TERMINAL_TYPE_STRING_MAP


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

StringType
NonTerminal::to_string( ) const
{
    return NonTerminalTypeStringMap[ type( ) ];
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

std::ostream&
operator<<( std::ostream& os, const NonTerminalPtr& non_terminal )
{
    return os << static_cast< SymbolPtr >( non_terminal );
}
