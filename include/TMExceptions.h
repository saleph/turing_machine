#ifndef TMEXCEPTIONS_H_INCLUDED
#define TMEXCEPTIONS_H_INCLUDED

#include <stdexcept>
using std::invalid_argument;

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

class InvalidCommand : invalid_argument {
    public:
        InvalidCommand() : invalid_argument ( "Invalid number of tokens in command!" ) {}
};


#endif // TMEXCEPTIONS_H_INCLUDED
