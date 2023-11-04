
#include "grammar/Grammar.hpp"

int
main( )
{
    Grammar golang;

    auto a = golang.define( TerminalGroup::NUMERIC, TerminalSubgroup::HEX );
    auto b = golang.define( TerminalGroup::NUMERIC, TerminalSubgroup::DECIMAL );
    auto c = NonTerminal::InvalidNonTerminal( );
    auto d = NonTerminal::InvalidNonTerminal( );

    golang.add_rule( c, a, b );
    golang.add_rule( c, c, c, c, b, a, a, c, d, d, a );

    return 0;
}
