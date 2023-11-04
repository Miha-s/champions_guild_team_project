#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include <unordered_map>
#include "grammar/Grammar.hpp"
#include "grammar/TypesSet.hpp"

using SymbolsSet = TypesSet< Symbols, SymbolsHash >;

using NonTerminalWithTerminals = std::unordered_map< SymbolPtr, SymbolsSet >;

NonTerminalWithTerminals first_k( const Grammar& grammar, int k );
NonTerminalWithTerminals follow_k( const Grammar& grammar, int k );

NonTerminals epsilon_non_terminals( const Grammar& grammar );
bool is_left_recursive( const Grammar& grammar, const NonTerminal& symbol );

#endif  // ALGORITHMS_HPP
