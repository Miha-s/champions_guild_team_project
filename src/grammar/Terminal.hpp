#ifndef TERMINAL_HPP
#define TERMINAL_HPP
#include <vector>

#include "Symbol.hpp"
#include "SymbolType.hpp"
#include "structures/Set.hpp"

enum class TerminalGroup : SymbolId;

enum class TerminalSubgroup : SymbolId;

struct Terminal : public Symbol
{
    SymbolType< TerminalGroup, TerminalSubgroup > type;
    StringType word;

    Terminal( )
        : Symbol{ true }
    {
    }

    Terminal( TerminalGroup group, TerminalSubgroup subgroup, StringType word )
        : Symbol{ true }
        , type{ group, subgroup }
        , word{ std::move( word ) }
    {
    }

    bool is_valid( ) const;

    bool
    operator==( const Terminal& other ) const
    {
        return type == other.type;
    }
};

struct TerminalHash
{
    std::size_t
    operator( )( const Terminal& terminal ) const
    {
        return std::hash< std::size_t >( )(
                static_cast< std::size_t >( terminal.type.group )
                ^ static_cast< std::size_t >( terminal.type.sub_group ) );
    }
};

enum class TerminalGroup : SymbolId
{
    INVALID
};

enum class TerminalSubgroup : SymbolId
{
    INVALID
};

bool
Terminal::is_valid( ) const
{
    return type.group != TerminalGroup::INVALID && type.sub_group != TerminalSubgroup::INVALID;
}

static const Terminal INVALID_TERMINAL =
        Terminal{ TerminalGroup::INVALID, TerminalSubgroup::INVALID, "" };

using Terminals = std::vector< Terminal >;
using TerminalsSet = Set< Terminals >;

#endif  // TERMINAL_HPP
