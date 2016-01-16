#ifndef TMCOMMAND_H
#define TMCOMMAND_H

#include "TMHeadMoveType.h"
#include <string>
using std::string;


class TMCommand {
    public:
        TMCommand() {}
        TMCommand(char from, char to, TMHeadMoveType moveType, string name)
            : fromState(from), toState(to), headMove(moveType), nextCommandName(name) {}
        TMCommand(const TMCommand&) = default;
        TMCommand(TMCommand&&) = default;
        TMCommand& operator= (const TMCommand&) = default;
        TMCommand& operator= (TMCommand&&) = default;

        bool operator== (const TMCommand& other) const {
            return this->fromState == other.fromState;
        }
        bool isTheSameAs (const TMCommand& other) const {
            bool statement = (this->fromState == other.fromState && this->toState == other.toState &&
                this->headMove == other.headMove && !(this->nextCommandName.compare(other.nextCommandName)));
            return statement;
        }
    private:
        char fromState;
        char toState;
        TMHeadMoveType headMove;
        string nextCommandName;
};

#endif // TMCOMMAND_H
