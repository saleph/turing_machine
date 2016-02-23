#ifndef TMEXCEPTIONS_H_INCLUDED
#define TMEXCEPTIONS_H_INCLUDED

#include <stdexcept>

class TMException : public std::invalid_argument {
    public:
        TMException(const std::string& arg)
            : std::invalid_argument (arg)
        {}
        // ctor with clarification
        TMException(const std::string& arg, const std::string& additional)
            : std::invalid_argument ( arg + std::string(":\n") + additional )
        {}
};

class MismatchCommandAndElementUnderHead : public TMException {
    public:
        MismatchCommandAndElementUnderHead()
            : TMException ( "Mismatch of command and the element under the head" )
        {}
};

class ZeroLongTape : public TMException {
    public:
        ZeroLongTape()
            : TMException ( "The tape cannot be zero-element-long" )
        {}
};

class HeadOutOfTape : public TMException {
    public:
        HeadOutOfTape()
            : TMException ( "The head position has cannot be larger than tapeSize - 1" )
        {}
};

class CharacterOutOfAlphabet : public TMException {
    public:
        CharacterOutOfAlphabet(const char& arg)
            : TMException ( "Character on tape out of defined alphabet", std::string(&arg, 1) )
        {}
};

class InvalidCommandSyntax : public TMException {
    public:
        InvalidCommandSyntax(const std::string& cmd)
            : TMException ( "Invalid syntax of command", cmd )
        {}
};

class CommandAlreadyExist : public TMException {
    public:
        CommandAlreadyExist(const std::string& cmd)
            : TMException ( "Command with this transition already exist", cmd )
        {}
};

class CommandNotExist : public TMException {
    public:
        CommandNotExist(const char& arg)
            : TMException ( "Command with this transition doesn't exist", std::string(&arg, 1) )
        {}
};

class EndOfTheControlGraph : public TMException {
    public:
        EndOfTheControlGraph()
            : TMException ( "End of the control graph (the machine reach state 'Stop')" )
        {}
};

class DataFromFileDoesntInserted : public TMException {
    public:
        DataFromFileDoesntInserted()
            : TMException ( "Data doesn't loaded properly" )
        {}
};

// === FILE PARSING EXCEPTIONS ===

class TMFileSyntaxException : public TMException {
    public:
        TMFileSyntaxException(const std::string& arg)
            : TMException ( std::string("File damaged: ") + arg )
        {}
};

class TMInvalidAlphabetSyntax : public TMFileSyntaxException {
    public:
        TMInvalidAlphabetSyntax()
            : TMFileSyntaxException ( "invalid alphabet syntax" )
        {}
};

class TMInvalidHeadPositionSyntax : public TMFileSyntaxException {
    public:
        TMInvalidHeadPositionSyntax()
            : TMFileSyntaxException ( "invalid head position syntax" )
        {}
};

class TMInvalidTapeContentSyntax : public TMFileSyntaxException {
    public:
        TMInvalidTapeContentSyntax()
            : TMFileSyntaxException ( "invalid tape content syntax" )
        {}
};

class TMInvalidControlGraphSyntax : public TMFileSyntaxException {
    public:
        TMInvalidControlGraphSyntax()
            : TMFileSyntaxException ( "invalid control graph syntax" )
        {}
};

#endif // TMEXCEPTIONS_H_INCLUDED
