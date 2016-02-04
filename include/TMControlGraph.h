#ifndef TMCONTROLGRAPH_H
#define TMCONTROLGRAPH_H

#include "TMCommand.h"
#include "TMStringCharPair.h"
#include "TMExceptions.h"
#include <unordered_map>
#include <string>
#include <memory>
using std::unordered_map;
using std::string;
using std::pair;
using std::move;


class TMControlGraph
{
    public:
        TMControlGraph() = default;
        TMControlGraph(const TMControlGraph&) = default;
        TMControlGraph& operator= (const TMControlGraph&) = default;
        TMControlGraph& operator= (TMControlGraph&&) = default;

        const TMCommand& operator[] (const TMStringCharPair& val) { return graph[val]; }
        void operator+= (const pair<string, TMCommand>& cmd) throw (CommandAlreadyExist);
        void addNewCmd(const pair<string, TMCommand>&) throw (CommandAlreadyExist);
    private:
        unordered_map<TMStringCharPair, TMCommand> graph;

        //void addNewCmd(const pair<string, TMCommand>&) throw (CommandAlreadyExist);
        void checkIfIsUnique(const TMStringCharPair&) throw (CommandAlreadyExist);
        void appendCmd(TMStringCharPair&, TMCommand&);
};

#endif // TMCONTROLGRAPH_H
