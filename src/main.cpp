
#include "grammar/Grammar.hpp"

int
main( )
{
    Grammar golang;

    Terminal a = golang.define( TerminalGroup::NUMERIC, TerminalSubgroup::HEX );
    Terminal b = golang.define( TerminalGroup::NUMERIC, TerminalSubgroup::DECIMAL );
    NonTerminal c = NonTerminal::INVALID_NON_TERMINAL;
    NonTerminal d = NonTerminal::INVALID_NON_TERMINAL;

    golang.add_rule( c, a, b );
    golang.add_rule( c, c, c, c, b, a, a, c, d, d, a );

    return 0;
}
