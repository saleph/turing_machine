#ifndef TMEXCEPTIONS_H_INCLUDED
#define TMEXCEPTIONS_H_INCLUDED

#include <stdexcept>
using std::invalid_argument;
using std::logic_error;

class MismatchCommandAndElementUnderHead : public invalid_argument {
    public:
        MismatchCommandAndElementUnderHead() : invalid_argument ( "Mismatch of command and the element under the head!" ) {};
};

class ZeroLongTape : public invalid_argument {
    public:
        ZeroLongTape() : invalid_argument ( "The tape cannot be zero-element-long!" ) {}
};

class HeadOutOfTape : public invalid_argument {
    public:
        HeadOutOfTape() : invalid_argument ( "The head position has cannot be larger than tapeSize - 1!" ) {}
};

class CharacterOutOfAlphabet : invalid_argument {
    public:
        CharacterOutOfAlphabet() : invalid_argument ( "Character out of defined alphabet!" ) {}
};

class InvalidCommandSyntax : invalid_argument {
    public:
        InvalidCommandSyntax() : invalid_argument ( "Invalid syntax of command!" ) {}
};

class CommandAlreadyExist : invalid_argument {
    public:
        CommandAlreadyExist() : invalid_argument ( "Command with this transition already exist!" ) {}
};

class EndOfTheControlGraph : logic_error {
    public:
        EndOfTheControlGraph() : logic_error ( "End of the control graph (the machine reach state 'Stop'!" ) {}
};


#endif // TMEXCEPTIONS_H_INCLUDED
