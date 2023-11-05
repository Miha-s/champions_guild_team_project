#ifndef SYNTAXRULE_H
#define SYNTAXRULE_H

#include <vector>

#include "Countable.hpp"
#include "NonTerminal.hpp"

class SyntaxRule
{
public:
    template < typename... SymbolsT >
    SyntaxRule( SymbolId id, NonTerminalPtr left_side, const SymbolsT&... right_side )
        : m_id{ id }
        , m_left_side{ left_side }
        , m_right_side{ right_side... }
    {
    }

    SymbolId id( ) const;

    bool is_valid( ) const;

    NonTerminalPtr get_left_side( ) const;

    Symbols get_right_side( ) const;

    bool contains( const SymbolPtr& symbol ) const;

    static std::shared_ptr< const SyntaxRule > InvalidRule( );

private:
    SymbolId m_id = INVALID_ID;
    NonTerminalPtr m_left_side;
    Symbols m_right_side;
};


using SyntaxRulePtr = std::shared_ptr< const SyntaxRule >;
using SyntaxRules = std::vector< SyntaxRulePtr >;
using SymbolRuleMap = std::unordered_map< SymbolPtr, SyntaxRulePtr >;

std::ostream& operator<<( std::ostream& os, const SyntaxRule& rule );
std::ostream& operator<<( std::ostream& os, const SyntaxRulePtr& rule );
std::ostream& operator<<( std::ostream& os, const SyntaxRules& rules );

#endif  // SYNTAXRULE_H
