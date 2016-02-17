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

class CharacterOutOfAlphabet : public TMException {
    public:
        CharacterOutOfAlphabet() : TMException ( "Character out of defined alphabet!" ) {}
};

class InvalidCommandSyntax : public TMException {
    public:
        InvalidCommandSyntax() : TMException ( "Invalid syntax of command!" ) {}
};

class CommandAlreadyExist : public TMException {
    public:
        CommandAlreadyExist() : TMException ( "Command with this transition already exist!" ) {}
};

class CommandNotExist : public TMException {
    public:
        CommandNotExist() : TMException ( "Command with this transition doesn't exist!" ) {}
};

class EndOfTheControlGraph : public TMException {
    public:
        EndOfTheControlGraph() : TMException ( "End of the control graph (the machine reach state 'Stop'!" ) {}
};

class DataFromFileDoesntInserted : public TMException {
    public:
        DataFromFileDoesntInserted() : TMException ( "Data doesn't loaded properly!" ) {}
};

// === FILE PARSING EXCEPTIONS ===

class TMFileSyntaxException : public TMException {
    public:
        TMFileSyntaxException(const std::string& arg) : TMException (arg) {}
};

class TMInvalidAlphabetSyntax : public TMFileSyntaxException {
    public:
        TMInvalidAlphabetSyntax() : TMFileSyntaxException ( "Invalid alphabet syntax!" ) {}
};

class TMInvalidHeadPositionSyntax : public TMFileSyntaxException {
    public:
        TMInvalidHeadPositionSyntax() : TMFileSyntaxException ( "Invalid head position syntax!" ) {}
};

class TMInvalidTapeContentSyntax : public TMFileSyntaxException {
    public:
        TMInvalidTapeContentSyntax() : TMFileSyntaxException ( "Invalid tape content syntax!" ) {}
};

class TMInvalidControlGraphSyntax : public TMFileSyntaxException {
    public:
        TMInvalidControlGraphSyntax() : TMFileSyntaxException ( "Invalid tape content syntax!" ) {}
};

#endif // TMEXCEPTIONS_H_INCLUDED
