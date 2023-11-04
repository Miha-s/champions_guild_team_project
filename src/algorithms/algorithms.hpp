#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include <unordered_map>
#include "grammar/Grammar.hpp"

using TerminalsSet = std::unordered_set< Terminals, TerminalsHash >;

using NonTerminalWithTerminals = std::unordered_map< NonTerminalPtr, TerminalsSet >;

NonTerminalWithTerminals first_k( const Grammar& grammar, int k );
NonTerminalWithTerminals follow_k( const Grammar& grammar, int k );

NonTerminals epsilon_non_terminals( const Grammar& grammar );
bool is_left_recursive( const Grammar& grammar, const NonTerminal& symbol );

#endif  // ALGORITHMS_HPP
