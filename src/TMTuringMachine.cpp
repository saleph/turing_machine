#include "TMTuringMachine.h"

TMTuringMachine::TMTuringMachine(size_t length) {
    alphabet = std::make_shared<TMAlphabet>();
    tape = std::make_shared<TMTape>(length, alphabet);
    parser = std::make_unique<TMCommandParser>();
    graph = std::make_unique<TMControlGraph>();
    currentCmdName = startPhrase;
}

void TMTuringMachine::addToGraph(const std::string& commandAsText) {
    *graph += parser->parseToCommandWithItsName(commandAsText);
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
}

void TMTuringMachine::checkIfTheGraphReachedEnd() const throw (EndOfTheControlGraph) {
    if (currentCmdName == endPhrase) throw EndOfTheControlGraph();
}

void TMTuringMachine::backTheGraphToTheBeginning() {
    currentCmdName = startPhrase;
}
