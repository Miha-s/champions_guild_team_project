#include "algorithms.hpp"

#include "vector"

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
        for ( const SyntaxRule& rule : grammar.get_grammar_rules( ) )
        {
            const auto& rightHandSide = rule.get_right_side( );
            SymbolsSet tmp_rule_set;
            auto& current_rule_set = firstSets[ rule.get_left_side( ) ];
            auto initia_size = current_rule_set.size( );

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
                const auto& right_side = rule.get_right_side( );
                auto it = std::find( right_side.begin( ), right_side.end( ), non_terminal );
                it++;
                SymbolsSet tmp_set;

                while ( it != right_side.end( ) )
                {
                    tmp_set.add_k( firstSets[ *it ], k );
                    it++;
                }

                tmp_set.add_k( followSets[ rule.get_left_side( ) ], k );

                followSets[ non_terminal ].unite_with( tmp_set );
            }
        }
    }

    return followSets;
}
