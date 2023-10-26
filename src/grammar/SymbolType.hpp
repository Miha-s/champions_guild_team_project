#ifndef SYMBOLTYPE_HPP
#define SYMBOLTYPE_HPP

template < typename Group, typename SubGroup >
struct SymbolType
{
    Group group;
    SubGroup sub_group;

    bool
    operator==( const SymbolType& other ) const
    {
        return group == other.group && sub_group == other.sub_group;
    }
};

#endif  // SYMBOLTYPE_HPP
