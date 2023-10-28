
#include "grammar/Grammar.hpp"

int
main( )
{
    Terminal a;
    Terminal b;
    NonTerminal c;
    NonTerminal d;


    Grammar golang;

    golang.add_rule( c, a, b );
    golang.add_rule( c, c, c, c, b, a, a, c, d, d, a );

    return 0;
}
