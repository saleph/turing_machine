#include "TMAPI.h"

void TMAPI::insertGraph(const std::initializer_list<std::string>& graphAsList) {
    graphAsText = graphAsList;
}

void TMAPI::insertAlphabet(const std::string& alphabet) {
    *turingMachine.alphabet = alphabet;
}

void TMAPI::setHeadPosition(const size_t pos) {
    tape->setHeadPosition(pos);
}

void TMAPI::compileInsertedGraph() {
    turingMachine.graph->clear();
    for (const auto commandAsText : graphAsText) turingMachine.addToGraph(commandAsText);
}

void TMAPI::doSingleStep() {
    turingMachine.doStep();
}

void TMAPI::executeGraphInstantly() {
    turingMachine.executeGraphInstantly();
}

void TMAPI::turnBackGraphToStartPosition() {
    turingMachine.backTheGraphToTheBeginning();
}
