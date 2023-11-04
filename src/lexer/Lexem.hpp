#ifndef LEXEM_HPP
#define LEXEM_HPP
#include "grammar/Terminal.hpp"

struct Position
{
    size_t row;
    size_t column;

    bool
    operator==( const Position& other ) const
    {
        return row == other.row && column == other.column;
    }
};

struct Lexem
{
    Terminal::Type type;
    Position pos;
    StringType word;

    Lexem( )
        : type{ TerminalGroup::INVALID, TerminalSubgroup::INVALID }
    {
    }

    Lexem( const Terminal::Type type, const Position& pos, const StringType& word )
        : type{ type }
        , pos{ pos }
        , word{ word }
    {
    }

    bool
    operator==( const Lexem& other ) const
    {
        return type == other.type && pos == other.pos && word == other.word;
    }

    bool
    is_valid( ) const
    {
        return type.group != TerminalGroup::INVALID && type.sub_group != TerminalSubgroup::INVALID;
    }
};

#endif // LEXEM_HPP
