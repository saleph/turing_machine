#include "TMControlGraph.h"

void TMControlGraph::operator+= (const pair<string, TMCommand>& cmd) throw (CommandAlreadyExist) {
    addNewCmd(cmd);
}

void TMControlGraph::addNewCmd(const pair<string, TMCommand>& cmd) throw (CommandAlreadyExist) {
    string commandName (cmd.first);
    TMCommand commandBody (cmd.second);
    TMStringCharPair cmdNameAndFromState (commandName, commandBody.getFromState());
    checkIfIsUnique(cmdNameAndFromState);
    appendCmd(cmdNameAndFromState, commandBody);
}

void TMControlGraph::checkIfIsUnique(const TMStringCharPair& cmdNameAndFromState) throw (CommandAlreadyExist) {

}

void TMControlGraph::appendCmd(TMStringCharPair& cmdNameAndFromState, TMCommand& commandBody) {
    graph[cmdNameAndFromState] = commandBody;
}
