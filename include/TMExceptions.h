#ifndef TMEXCEPTIONS_H_INCLUDED
#define TMEXCEPTIONS_H_INCLUDED

#include <stdexcept>

class TMException : public std::invalid_argument {
    public:
        TMException(const std::string& arg) : std::invalid_argument (arg) {}
};

class MismatchCommandAndElementUnderHead : public TMException {
    public:
        MismatchCommandAndElementUnderHead() : TMException ( "Mismatch of command and the element under the head!" ) {};
};

class ZeroLongTape : public TMException {
    public:
        ZeroLongTape() : TMException ( "The tape cannot be zero-element-long!" ) {}
};

class HeadOutOfTape : public TMException {
    public:
        HeadOutOfTape() : TMException ( "The head position has cannot be larger than tapeSize - 1!" ) {}
};

class CharacterOutOfAlphabet : TMException {
    public:
        CharacterOutOfAlphabet() : TMException ( "Character out of defined alphabet!" ) {}
};

class InvalidCommandSyntax : TMException {
    public:
        InvalidCommandSyntax() : TMException ( "Invalid syntax of command!" ) {}
};

class CommandAlreadyExist : TMException {
    public:
        CommandAlreadyExist() : TMException ( "Command with this transition already exist!" ) {}
};

class CommandNotExist : TMException {
    public:
        CommandNotExist() : TMException ( "Command with this transition doesn't exist!" ) {}
};

class EndOfTheControlGraph : TMException {
    public:
        EndOfTheControlGraph() : TMException ( "End of the control graph (the machine reach state 'Stop'!" ) {}
};


#endif // TMEXCEPTIONS_H_INCLUDED
