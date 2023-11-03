#include "algorithms.hpp"

#include "vector"

std::unordered_set< Symbols, SymbolsHash >
kAddition( const std::vector< std::unordered_set< Symbols, SymbolsHash > >& symbolLists, int k )
{
    if ( symbolLists.empty( ) )
    {
        return { };
    }

    for ( auto const& symbol_set : symbolLists )
    {
        if ( symbol_set.empty( ) )
        {
            return { };
        }
    }

    std::unordered_set< Symbols, SymbolsHash > result = symbolLists[ 0 ];

    for ( size_t i = 1; i < symbolLists.size( ); ++i )
    {
        std::unordered_set< Symbols, SymbolsHash > tempResult;

        for ( Symbols current : result )
        {
            for ( Symbols next : symbolLists[ i ] )
            {
                if ( current.size( ) == 1 && Grammar::is_epsilon( current.at( 0 ) ) )
                {
                    current.erase( current.begin( ) );
                }

                Symbols combined;
                combined.insert( combined.end( ), current.begin( ), current.end( ) );

                if ( next.size( ) == 1 && Grammar::is_epsilon( next.at( 0 ) ) )
                {
                    tempResult.insert( combined );
                    continue;
                }

                if ( next.size( ) + combined.size( ) > k )
                {
                    for ( int j = 0; j < k - combined.size( ); j++ )
                    {
                        combined.push_back( next.at( j ) );
                    }
                }
                else
                {
                    combined.insert( combined.end( ), next.begin( ), next.end( ) );
                }

                tempResult.insert( combined );
            }
        }

        result = tempResult;
    }

    return result;
}

TerminalsSet
kAddition( const std::vector< TerminalsSet >& symbolLists, int k )
{
    if ( symbolLists.empty( ) )
    {
        return { };
    }

    for ( auto const& symbol_set : symbolLists )
    {
        if ( symbol_set.empty( ) )
        {
            return { };
        }
    }

    std::unordered_set< Terminals, TerminalsHash > result = symbolLists[ 0 ];

    for ( size_t i = 1; i < symbolLists.size( ); ++i )
    {
        std::unordered_set< Terminals, TerminalsHash > tempResult;

        for ( Terminals current : result )
        {
            for ( Terminals next : symbolLists[ i ] )
            {
                if ( current.size( ) == 1 && Grammar::is_epsilon( current.at( 0 ) ) )
                {
                    current.erase( current.begin( ) );
                }

                Terminals combined;
                combined.insert( combined.end( ), current.begin( ), current.end( ) );

                if ( next.size( ) == 1 && Grammar::is_epsilon( next.at( 0 ) ) )
                {
                    if (combined.empty()) {
                        tempResult.insert(next);
                    } else {
                        tempResult.insert( combined );
                        continue;
                    }
                }

                if ( next.size( ) + combined.size( ) > k )
                {
                    for ( int j = 0; j < k - combined.size( ); j++ )
                    {
                        combined.push_back( next.at( j ) );
                    }
                }
                else
                {
                    combined.insert( combined.end( ), next.begin( ), next.end( ) );
                }

                tempResult.insert( combined );
            }
        }

        result = tempResult;
    }

    return result;
}

std::unordered_set< Symbols, SymbolsHash >
multiply( const std::vector< std::unordered_set< Symbols, SymbolsHash > >& symbolLists )
{
    if ( symbolLists.empty( ) )
    {
        return { };
    }

    for ( auto const& symbol_set : symbolLists )
    {
        if ( symbol_set.empty( ) )
        {
            return { };
        }
    }

    std::unordered_set< Symbols, SymbolsHash > result = symbolLists[ 0 ];

    for ( size_t i = 1; i < symbolLists.size( ); ++i )
    {
        std::unordered_set< Symbols, SymbolsHash > tempResult;

        for ( Symbols current : result )
        {
            for ( Symbols next : symbolLists[ i ] )
            {
                if ( current.size( ) == 1 && Grammar::is_epsilon( current.at( 0 ) ) )
                {
                    current.erase( current.begin( ) );
                }

                Symbols combined;
                combined.insert( combined.end( ), current.begin( ), current.end( ) );

                if ( next.size( ) == 1 && Grammar::is_epsilon( next.at( 0 ) ) )
                {
                    tempResult.insert( combined );
                    continue;
                }

                combined.insert( combined.end( ), next.begin( ), next.end( ) );

                tempResult.insert( combined );
            }
        }

        result = tempResult;
    }

    return result;
}

std::unordered_set< Terminals, TerminalsHash >
multiply( const std::vector< std::unordered_set< Terminals, TerminalsHash > >& symbolLists )
{
    if ( symbolLists.empty( ) )
    {
        return { };
    }

    for ( auto const& symbol_set : symbolLists )
    {
        if ( symbol_set.empty( ) )
        {
            return { };
        }
    }

    std::unordered_set< Terminals, TerminalsHash > result = symbolLists[ 0 ];

    for ( size_t i = 1; i < symbolLists.size( ); ++i )
    {
        std::unordered_set< Terminals, TerminalsHash > tempResult;

        for ( Terminals current : result )
        {
            for ( Terminals next : symbolLists[ i ] )
            {
                if ( current.size( ) == 1 && Grammar::is_epsilon( current.at( 0 ) ) )
                {
                    current.erase( current.begin( ) );
                }

                Terminals combined;
                combined.insert( combined.end( ), current.begin( ), current.end( ) );

                if ( next.size( ) == 1 && Grammar::is_epsilon( next.at( 0 ) ) )
                {
                    tempResult.insert( combined );
                    continue;
                }

                combined.insert( combined.end( ), next.begin( ), next.end( ) );

                tempResult.insert( combined );
            }
        }

        result = tempResult;
    }

    return result;
}

NonTerminalWithTerminals
first_k( Grammar& grammar, int k )
{
    std::unordered_map< Symbol, std::unordered_set< Symbols, SymbolsHash >, SymbolHash > firstSets =
            std::unordered_map< Symbol, std::unordered_set< Symbols, SymbolsHash >, SymbolHash >{ };

    for ( const NonTerminal& nonTerminal : grammar.get_non_terminals( ) )
    {
        firstSets[ nonTerminal ] = { };
    }

    bool updated = true;
    while ( updated )
    {
        updated = false;
        for ( const SyntaxRule& rule : grammar.get_grammar_rules( ) )
        {
            const auto& rightHandSide = rule.get_right_side( );

            std::vector< std::unordered_set< Symbols, SymbolsHash > > to_add_symbols;

            for ( const Symbol& symbol : rightHandSide )
            {
                if ( symbol.is_terminal( ) )
                {
                    to_add_symbols.push_back(
                            std::unordered_set< Symbols, SymbolsHash >{ Symbols{ symbol } } );
                }
                else
                {
                    to_add_symbols.push_back( firstSets[ symbol ] );
                }
            }
            auto addition_result = kAddition( to_add_symbols, k );

            if ( addition_result.size( ) > firstSets[ rule.get_left_side( ) ].size( ) )
            {
                updated = true;
            }

            for ( const Symbols& s : addition_result )
            {
                firstSets[ rule.get_left_side( ) ].insert( s );
            }
        }
    }

    NonTerminalWithTerminals result;
    for ( const NonTerminal& nonTerminal : grammar.get_non_terminals( ) )
    {
        TerminalsSet terminals_set = TerminalsSet{ };
        for ( const auto& vector_of_symbols : firstSets[ nonTerminal ] )
        {
            Terminals terminals;
            for ( const auto symbol : vector_of_symbols )
            {
                terminals.push_back( grammar.get_terminal_by_id( symbol.id( ) ) );
            }
            terminals_set.insert( terminals );
        }
        result[ nonTerminal ] = terminals_set;
    }
    return result;
}

NonTerminalWithTerminals
follow_k( Grammar& grammar, int k )
{
    std::unordered_map< NonTerminal,
                        std::unordered_set< Terminals, TerminalsHash >,
                        NonTerminalHash >
            firstSets;

    for ( const NonTerminal& nonTerminal : grammar.get_non_terminals( ) )
    {
        firstSets[ nonTerminal ] = { };
    }

    firstSets[ *grammar.get_non_terminals( ).begin( ) ] =
            ( TerminalsSet{ Terminals{ grammar.get_terminal_by_id( EPSILON_ID ) } } );


        for ( const SyntaxRule& rule : grammar.get_grammar_rules( ) )
        {
            for ( const SyntaxRule& rule_inner : grammar.get_grammar_rules( ) )
            {
                for ( int i = 0; i < rule_inner.get_right_side( ).size( ); i++ )
                {
                    if ( rule_inner.get_right_side( )[ i ] == rule.get_left_side( ) )
                    {
                        std::vector< TerminalsSet > result_of_first_k;
                        for ( int j = i + 1; j < rule_inner.get_right_side( ).size( ); j++ )
                        {
                            if ( rule_inner.get_right_side( )[ j ].is_terminal( ) )
                            {
                                result_of_first_k.push_back( std::unordered_set< Terminals,
                                                                                 TerminalsHash >{
                                        Terminals{ grammar.get_terminal_by_id(
                                                rule_inner.get_right_side( )[ j ].id( ) ) } } );
                            }
                            else
                            {
                                result_of_first_k.push_back(
                                        first_k( grammar, k )[ grammar.get_non_terminal_by_id(
                                                rule_inner.get_right_side( )[ j ].id( ) ) ] );
                            }
                        }

                        if ( result_of_first_k.empty() )
                        {
                            result_of_first_k.push_back( TerminalsSet{
                                    Terminals{ grammar.get_terminal_by_id( EPSILON_ID ) } } );
                        }

                        auto addition = kAddition( result_of_first_k, k );

                        for ( const Terminals& t : addition )
                        {
                            firstSets[ rule.get_left_side( ) ].insert( t );
                        }
                    }
                }
            }
        }

    bool updated = true;
    while ( updated )
    {
        updated = false;
        for ( const SyntaxRule& rule : grammar.get_grammar_rules( ) )
        {
            for ( const SyntaxRule& rule_inner : grammar.get_grammar_rules( ) )
            {
                for ( int i = 0; i < rule_inner.get_right_side( ).size( ); i++ )
                {
                    if ( rule_inner.get_right_side( )[ i ] == rule.get_left_side( ) )
                    {
                        std::vector< TerminalsSet > result_of_first_k;
                        for ( int j = i + 1; j < rule_inner.get_right_side( ).size( ); j++ )
                        {
                            if ( rule_inner.get_right_side( )[ j ].is_terminal( ) )
                            {
                                result_of_first_k.push_back( std::unordered_set< Terminals,
                                                                                 TerminalsHash >{
                                        Terminals{ grammar.get_terminal_by_id(
                                                rule_inner.get_right_side( )[ j ].id( ) ) } } );
                            }
                            else
                            {
                                result_of_first_k.push_back(
                                        first_k( grammar, k )[ grammar.get_non_terminal_by_id(
                                                rule_inner.get_right_side( )[ j ].id( ) ) ] );
                            }
                        }

                        if ( result_of_first_k.empty() )
                        {
                            result_of_first_k.push_back( TerminalsSet{
                                    Terminals{ grammar.get_terminal_by_id( EPSILON_ID ) } } );
                        }

                        result_of_first_k.push_back( firstSets[ rule_inner.get_left_side( ) ] );

                        auto addition = kAddition( result_of_first_k, k );

                        if ( addition.size( ) > firstSets[ rule.get_left_side( ) ].size( ) )
                        {
                            updated = true;
                        }

                        for ( const Terminals& t : addition )
                        {
                            firstSets[ rule.get_left_side( ) ].insert( t );
                        }
                    }
                }
            }
        }
    }
    return firstSets;
}