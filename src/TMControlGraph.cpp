#include "TMControlGraph.h"

const TMCommand& TMControlGraph::operator[] (const TMStringCharPair& val) const throw (CommandNotExist) {
    try {
        return graph.at(val);
    } catch (const std::out_of_range&) {
        const char currentCharOnTape = val.character;
        throw CommandNotExist(currentCharOnTape);
    }
}

void TMControlGraph::operator+= (const std::pair<std::string, TMCommand>& cmd) throw (CommandAlreadyExist) {
    addNewCmd(cmd);
}

void TMControlGraph::addNewCmd(const std::pair<std::string, TMCommand>& cmd) throw (CommandAlreadyExist) {
    std::string commandName (cmd.first);
    TMCommand commandBody (cmd.second);
    TMStringCharPair cmdNameAndFromState (commandName, commandBody.getFromState());
    checkIfIsUnique(cmdNameAndFromState);
    appendCmd(cmdNameAndFromState, commandBody);
}

void TMControlGraph::checkIfIsUnique(const TMStringCharPair& cmdNameAndFromState) throw (CommandAlreadyExist) {
    size_t numberOfOccurences = graph.count(cmdNameAndFromState);
    if (numberOfOccurences >= 1) {
        std::string cmd = "Command name: ";
        cmd += cmdNameAndFromState.name;
        cmd += ", from state: ";
        cmd += cmdNameAndFromState.character;
        throw CommandAlreadyExist(cmd);
    }
}

void TMControlGraph::appendCmd(TMStringCharPair& cmdNameAndFromState, TMCommand& commandBody) {
    graph[cmdNameAndFromState] = commandBody;
}

void TMControlGraph::clear() {
    graph.clear();
}
