#include "algorithms.hpp"

#include "vector"

std::ostream&
operator<<( std::ostream& os, const SymbolsSet& symbols_set )
{
    os << "{";
    for ( auto it = symbols_set.begin( ); it != symbols_set.end( ); )
    {
        os << *it;
        if ( ++it != symbols_set.end( ) )
        {
            os << ", ";
        }
    }
    os << "}";
    return os;
}

std::ostream&
operator<<( std::ostream& os, const SymbolSymbolsMap& map )
{
    os << "{" << std::endl;
    for ( const auto& el : map )
    {
        os << "(" << el.first << ": " << el.second << ")" << std::endl;
    }
    os << "}";
    return os;
}

bool
check_for_empty_set( const Symbols& symbols, const SymbolSymbolsMap& map )
{
    for ( const auto& symbol : symbols )
    {
        if ( map.at( symbol ).size( ) == 0 )
        {
            return true;
        }
    }
    return false;
}

SymbolSymbolsMap
first_k( const Grammar& grammar, int k )
{
    SymbolSymbolsMap firstSets;

    for ( const auto& nonTerminal : grammar.get_non_terminals( ) )
    {
        firstSets[ nonTerminal ] = { };
    }

    for ( const auto& terminal : grammar.get_terminals( ) )
    {
        SymbolsSet tmp_set;
        tmp_set.insert( { terminal } );
        firstSets[ terminal ] = tmp_set;
    }

    SymbolsSet tmp_set;
    tmp_set.insert( { grammar.epsilon( ) } );
    firstSets[ grammar.epsilon( ) ] = tmp_set;

    bool updated = true;
    while ( updated )
    {
        updated = false;
        for ( const auto& rule : grammar.get_grammar_rules( ) )
        {
            const auto& rightHandSide = rule->get_right_side( );
            SymbolsSet tmp_rule_set;
            auto& current_rule_set = firstSets[ rule->get_left_side( ) ];
            auto initia_size = current_rule_set.size( );

            if ( check_for_empty_set( rule->get_right_side( ), firstSets ) )
            {
                continue;
            }

            for ( const auto& symbol : rightHandSide )
            {
                tmp_rule_set.add_k( firstSets[ symbol ], k );
            }

            current_rule_set.unite_with( tmp_rule_set );

            if ( current_rule_set.size( ) > initia_size )
            {
                updated = true;
            }
        }
    }

    return firstSets;
}

SymbolsSet
first_k( const Grammar& grammar, int k, const Symbols& symbols )
{
    SymbolSymbolsMap firstSets = first_k( grammar, k );
    SymbolsSet result;
    for ( const auto& symbol : symbols )
    {
        result.add_k( firstSets[ symbol ], k );
    }
    return result;
}

SymbolsSet
first_k( const Grammar& grammar, int k, Symbols::const_iterator it_begin, Symbols::const_iterator it_end )
{
    SymbolSymbolsMap firstSets = first_k( grammar, k );
    SymbolsSet result;
    for ( ; it_begin != it_end; )
    {
        result.add_k( firstSets[ *it_begin ], k );
        std::advance( it_begin, 1 );
    }

    return result;
}

SymbolSymbolsMap
follow_k( const Grammar& grammar, int k )
{
    SymbolSymbolsMap firstSets = first_k( grammar, k );
    SymbolSymbolsMap followSets;
    for ( const auto& nonTerminal : grammar.get_non_terminals( ) )
    {
        followSets[ nonTerminal ] = { };
    }
    SymbolsSet initial_set;
    initial_set.insert( { grammar.epsilon( ) } );

    followSets[ *grammar.get_non_terminals( ).begin( ) ] = initial_set;

    bool updated = true;
    while ( updated )
    {
        updated = false;
        for ( const auto& non_terminal : grammar.get_non_terminals( ) )
        {
            auto rules = grammar.syntax_rules_with_symbol( non_terminal );
            for ( const auto& rule : rules )
            {
                const auto& right_side = rule->get_right_side( );
                auto it = std::find( right_side.begin( ), right_side.end( ), non_terminal );
                SymbolsSet tmp_set;
                it++;

                while ( it != right_side.end( ) )
                {
                    tmp_set.add_k( firstSets[ *it ], k );
                    it++;
                }

                tmp_set.add_k( followSets[ rule->get_left_side( ) ], k );

                auto init_size = followSets[ non_terminal ].size( );

                followSets[ non_terminal ].unite_with( tmp_set );

                if ( init_size < followSets[ non_terminal ].size( ) )
                {
                    updated = true;
                }
            }
        }
    }

    return followSets;
}


