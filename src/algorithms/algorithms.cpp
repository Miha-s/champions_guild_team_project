#include "algorithms.hpp"

#include "vector"

bool
check_for_empty_set( const Symbols& symbols, const NonTerminalWithTerminals& map )
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

NonTerminalWithTerminals
first_k( const Grammar& grammar, int k )
{
    NonTerminalWithTerminals firstSets;

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

NonTerminalWithTerminals
follow_k( const Grammar& grammar, int k )
{
    NonTerminalWithTerminals firstSets = first_k( grammar, k );
    NonTerminalWithTerminals followSets;
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
