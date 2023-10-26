#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include "grammar/Grammar.hpp"

Terminals first_k( const Grammar& grammar, const Symbol& symbol, int k );
Terminals follow_k( const Grammar& grammar, const Symbol& symbol, int k );
NonTerminals epsilon_non_terminals(const Grammar& grammar);
bool is_left_recursive( const Grammar& grammar, const NonTerminal& symbol );

#endif // ALGORITHMS_HPP
