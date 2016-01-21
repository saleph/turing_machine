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
        virtual ~TMCommand() = default;

        char getFromState() { return fromState; }
        char getToState() { return toState; }
        const TMHeadMoveType& getHeadMove() { return headMove; }
        const string& getNextCommandName() { return nextCommandName; }

        bool operator== (const TMCommand& other) const {
            return fromState == other.fromState;
        }
        bool isTheSameAs (const TMCommand& other) const {
            return (fromState == other.fromState && toState == other.toState &&
                headMove == other.headMove && nextCommandName == other.nextCommandName);
        }
    private:
        char fromState;
        char toState;
        TMHeadMoveType headMove;
        string nextCommandName;
};

#endif // TMCOMMAND_H
