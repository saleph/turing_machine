#ifndef TMCOMMAND_H
#define TMCOMMAND_H

#include "TMHeadMoveType.h"
#include <string>


class TMCommand {
    public:
        TMCommand() {}
        TMCommand(char from, char to, TMHeadMoveType moveType, std::string& name, int loc=-1)
            : fromState(from), toState(to), headMove(moveType), nextCommandName(name), locationOfCommand(loc) {}
        TMCommand(char from, char to, TMHeadMoveType moveType, const char* name, int loc=-1)
            : fromState(from), toState(to), headMove(moveType), nextCommandName(name), locationOfCommand(loc) {}
        TMCommand(const TMCommand&) = default;
        TMCommand(TMCommand&&) = default;
        TMCommand& operator= (const TMCommand&) = default;
        TMCommand& operator= (TMCommand&&) = default;
        virtual ~TMCommand() = default;

        char getFromState() const { return fromState; }
        char getToState() const { return toState; }
        const TMHeadMoveType& getHeadMove() const { return headMove; }
        const std::string& getNextCommandName() const { return nextCommandName; }
        int getLocationOfCommand() const { return locationOfCommand; }

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
        std::string nextCommandName;
        int locationOfCommand;
};

#endif // TMCOMMAND_H
