#include "Symbol.hpp"


std::ostream&
operator<<( std::ostream& os, const Symbol& sym )
{
    return os << sym.to_string( );
}

std::ostream&
operator<<( std::ostream& os, const SymbolPtr& sym )
{
    return os << sym->to_string( );
}

std::ostream&
operator<<( std::ostream& os, const Symbols& syms )
{
    os << "(";
    for ( auto it = syms.begin(); it != syms.end(); )
    {
        os << *it;
        if ( ++it != syms.end( ) )
        {
            os << ", ";
        }
    }
    os << ")";
    return os;
}
