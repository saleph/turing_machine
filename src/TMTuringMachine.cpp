#include "TMTuringMachine.h"

TMTuringMachine::TMTuringMachine(unsigned int length=1001u) {
    alphabet = make_shared<TMAlphabet>();
    tape = make_shared<TMTape>(length, alphabet);
    parser = make_unique<TMCommandParser>();
    graph = make_unique<TMControlGraph>();
    currentCmdName = "Start";
}

void TMTuringMachine::addToGraph(const string& commandAsText) {
    *graph += parser->parseToCommandWithItsName(commandAsText);
}

void TMTuringMachine::doStep() {
    char currentState = tape->getCharUnderHead();
    TMStringCharPair currentCmdIndex (currentCmdName, currentState);
    TMCommand currentCmd = (*graph)[currentCmdIndex];
    doCommandOnTheTape(currentCmd);
}

void TMTuringMachine::doCommandOnTheTape(const TMCommand& cmd) {
    char currentState = tape->getCharUnderHead();
    char toState = cmd.getToState();
    TMHeadMoveType headMove = cmd.getHeadMove();
    tape->doCmd(currentState, toState, headMove);
    currentCmdName = cmd.getNextCommandName();
}
