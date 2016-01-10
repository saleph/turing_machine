#ifndef TMCOMMAND_H
#define TMCOMMAND_H

#include "TMHeadMoveType.h"
#include <string>
using std::string;


struct TMCommand {
    char fromState;
    char toState;
    TMHeadMoveType headMove;
    string nextCommandName;
};

#endif // TMCOMMAND_H
