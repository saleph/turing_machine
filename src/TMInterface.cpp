#include "TMInterface.h"

void TMInterface::insertGraph(const std::initializer_list<std::string>& graphAsList) {
    graphAsText = graphAsList;
}

void TMInterface::insertAlphabet(const std::string& alphabet) {
    turingMachine.alphabet->setAlphabet(alphabet);
}

void TMInterface::compileInstertedGraph() {
    for (const auto commandAsText : graphAsText) turingMachine.addToGraph(commandAsText);
}

void TMInterface::executeGraphInstantly() {
    turingMachine.instantExecution();
}
