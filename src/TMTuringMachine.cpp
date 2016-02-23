#include "TMTuringMachine.h"

TMTuringMachine::TMTuringMachine(size_t length) {
    alphabet = std::make_shared<TMAlphabet>();
    tape = std::make_shared<TMTape>(length, alphabet);
    parser = std::make_unique<TMCommandParser>();
    graph = std::make_unique<TMControlGraph>();
    currentCmdName = startPhrase;
    currentCmdLocation = -1;
}

void TMTuringMachine::addToGraph(const std::string& commandAsText, const int& location) {
    *graph += parser->parseToCommandWithItsName(commandAsText, location);
}

void TMTuringMachine::doStep() {
    char currentState = tape->getCharUnderHead();
    TMStringCharPair currentCmdIndex (currentCmdName, currentState);
    TMCommand currentCmd = (*graph)[currentCmdIndex];
    doCommandOnTheTape(currentCmd);
    checkIfTheGraphReachedEnd();
}

void TMTuringMachine::doCommandOnTheTape(const TMCommand& cmd) {
    char fromState = cmd.getFromState();
    char toState = cmd.getToState();
    TMHeadMoveType headMove = cmd.getHeadMove();
    tape->doCmd(fromState, toState, headMove);
    currentCmdName = cmd.getNextCommandName();
    currentCmdLocation = cmd.getLocationOfCommand();
}

void TMTuringMachine::checkIfTheGraphReachedEnd() const throw (EndOfTheControlGraph) {
    if (currentCmdName == endPhrase) throw EndOfTheControlGraph();
}

void TMTuringMachine::executeGraphInstantly() {
    try {
        for(;;) doStep();
    } catch (const EndOfTheControlGraph&) {}
}

void TMTuringMachine::backTheGraphToTheBeginning() {
    currentCmdName = startPhrase;
}

int TMTuringMachine::getLocationOfLastCommand() const {
    return currentCmdLocation;
}
