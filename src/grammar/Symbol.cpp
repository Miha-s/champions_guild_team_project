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
    for ( const auto& sym : syms )
    {
        os << sym;
        if ( sym != syms.back( ) )
        {
            os << ", ";
        }
    }
    os << ")";
    return os;
}
