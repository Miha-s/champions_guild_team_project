#include "SyntaxRule.hpp"

SymbolId
SyntaxRule::id( ) const
{
    return m_id;
}

bool
SyntaxRule::is_valid( ) const
{
    return m_id != INVALID_ID && m_left_side->is_valid( );
}

NonTerminalPtr
SyntaxRule::get_left_side( ) const
{
    return this->m_left_side;
}

Symbols
SyntaxRule::get_right_side( ) const
{
    return m_right_side;
}

bool
SyntaxRule::contains( const SymbolPtr& symbol ) const
{
    for ( const auto& item : m_right_side )
    {
        if ( item == symbol )
        {
            return true;
        }
    }
    return false;
}

std::shared_ptr< const SyntaxRule >
SyntaxRule::InvalidRule( )
{
    static std::shared_ptr< const SyntaxRule > invalid_rule(
            new SyntaxRule( INVALID_ID, NonTerminal::InvalidNonTerminal( ) ) );
    return invalid_rule;
}

std::ostream&
operator<<( std::ostream& os, const SyntaxRule& rule )
{
    if ( !rule.is_valid( ) )
    {
        os << "INVALID_RULE";
        return os;
    }
    os << rule.get_left_side( );
    os << " -> ";
    os << rule.get_right_side( );
    return os;
}

std::ostream&
operator<<( std::ostream& os, const SyntaxRulePtr& rule )
{
    return os << *rule;
}

std::ostream&
operator<<( std::ostream& os, const SyntaxRules& rules )
{
    os << "[" << std::endl;
    for ( const auto& rule : rules )
    {
        os << rule << std::endl;
    }
    os << "]";
    return os;
}
