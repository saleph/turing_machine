#ifndef TMEXCEPTIONS_H_INCLUDED
#define TMEXCEPTIONS_H_INCLUDED

#include <stdexcept>

class MismatchCommandAndElementUnderHead : public std::invalid_argument {
    public:
        MismatchCommandAndElementUnderHead() : std::invalid_argument ( "Mismatch of command and the element under the head!" ) {};
};

class ZeroLongTape : public std::invalid_argument {
    public:
        ZeroLongTape() : std::invalid_argument ( "The tape cannot be zero-element-long!" ) {}
};

class HeadOutOfTape : public std::invalid_argument {
    public:
        HeadOutOfTape() : std::invalid_argument ( "The head position has cannot be larger than tapeSize - 1!" ) {}
};

class CharacterOutOfAlphabet : std::invalid_argument {
    public:
        CharacterOutOfAlphabet() : std::invalid_argument ( "Character out of defined alphabet!" ) {}
};

class InvalidCommandSyntax : std::invalid_argument {
    public:
        InvalidCommandSyntax() : std::invalid_argument ( "Invalid syntax of command!" ) {}
};

class CommandAlreadyExist : std::invalid_argument {
    public:
        CommandAlreadyExist() : std::invalid_argument ( "Command with this transition already exist!" ) {}
};

class CommandNotExist : std::invalid_argument {
    public:
        CommandNotExist() : std::invalid_argument ( "Command with this transition doesn't exist!" ) {}
};

class EndOfTheControlGraph : std::logic_error {
    public:
        EndOfTheControlGraph() : std::logic_error ( "End of the control graph (the machine reach state 'Stop'!" ) {}
};


#endif // TMEXCEPTIONS_H_INCLUDED
