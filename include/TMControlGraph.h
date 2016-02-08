#ifndef TMCONTROLGRAPH_H
#define TMCONTROLGRAPH_H

#include "TMCommand.h"
#include "TMStringCharPair.h"
#include "TMExceptions.h"
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;
using std::pair;
using std::move;


class TMControlGraph
{
    public:
        TMControlGraph() {}

        const TMCommand& operator[] (const TMStringCharPair&) const throw (CommandNotExist);
        void operator+= (const pair<string, TMCommand>& cmd) throw (CommandAlreadyExist);
        void clear();
    private:
        unordered_map<TMStringCharPair, TMCommand> graph;

        void addNewCmd(const pair<string, TMCommand>&) throw (CommandAlreadyExist);
        void checkIfIsUnique(const TMStringCharPair&) throw (CommandAlreadyExist);
        void appendCmd(TMStringCharPair&, TMCommand&);
};

#endif // TMCONTROLGRAPH_H
