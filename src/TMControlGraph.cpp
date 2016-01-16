#include "TMControlGraph.h"

TMControlGraph TMControlGraph::operator+= (const pair<string, TMCommand>& cmd) {
    addNewCmd(cmd);
    return *this;
}

void TMControlGraph::addNewCmd(const pair<string, TMCommand>& cmd) {
    /*const string commandName (move(cmd.first));
    const TMCommand commandBody (move(cmd.second));
    checkIfIsUnique(commandBody);
    appendCmd(commandName, commandBody);*/
    // TODO: WRITE TESTS
}

void TMControlGraph::checkIfIsUnique(const TMCommand& cmdBody) const {

}

void TMControlGraph::appendCmd(const string& cmdName, const TMCommand& cmdBody) {

}
