#ifndef TERMINAL_HPP
#define TERMINAL_HPP
#include "Symbol.hpp"

struct Terminal : public Symbol {


    bool is_terminal() const override {
        return true;
    }
};

#endif // TERMINAL_HPP
