#ifndef SYNTAXRULE_H
#define SYNTAXRULE_H

#include <vector>

#include "Countable.hpp"
#include "NonTerminal.hpp"

class SyntaxRule
{
public:
    template <typename... Symbols>
    SyntaxRule( SymbolId id, NonTerminal left_side, const Symbols&... right_side )
        : m_id{ id }
        , m_left_side{ left_side }
        , m_right_side{ right_side... }
    {
    }

private:
    SymbolId m_id;
    NonTerminal m_left_side;
    Symbols  m_right_side;
};

#endif  // SYNTAXRULE_H
