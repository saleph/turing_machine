#include "TMTuringMachine.h"

TMTuringMachine::TMTuringMachine(size_t length) {
    alphabet = make_shared<TMAlphabet>();
    tape = make_shared<TMTape>(length, alphabet);
    parser = make_unique<TMCommandParser>();
    graph = make_unique<TMControlGraph>();
    currentCmdName = startPhrase;
}

void TMTuringMachine::addToGraph(const string& commandAsText) {
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
