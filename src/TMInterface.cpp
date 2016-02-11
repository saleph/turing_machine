#include "TMInterface.h"

void TMInterface::insertGraph(const std::initializer_list<std::string>& graphAsList) {
    graphAsText = graphAsList;
}

void TMInterface::compileInstertedGraph() {
    for (auto commandAsText : graphAsText) turingMachine.addToGraph(commandAsText);
}
