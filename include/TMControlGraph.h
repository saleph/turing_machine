#ifndef TMCONTROLGRAPH_H
#define TMCONTROLGRAPH_H

#include "TMCommand.h"
#include <unordered_map>
#include <string>
using std::unordered_multimap;
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

        TMControlGraph operator+= (const pair<string, TMCommand>& cmd);
    private:
        unordered_multimap<string, TMCommand> graph;

        void addNewCmd(const pair<string, TMCommand>&);
        void checkIfIsUnique(const TMCommand&) const;
        void appendCmd(const string&, const TMCommand&);
};

#endif // TMCONTROLGRAPH_H
