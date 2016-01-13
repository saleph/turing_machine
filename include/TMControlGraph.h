#ifndef TMCONTROLGRAPH_H
#define TMCONTROLGRAPH_H

#include "TMCommand.h"
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;
using std::pair;
using std::move;


class TMControlGraph
{
    public:
        TMControlGraph(const TMControlGraph&) = default;
        TMCommand& operator[] (const string& val) { return graph[val]; }
        TMControlGraph operator+= (const pair<string, TMCommand>& cmd);
    protected:
    private:
        unordered_map<string, TMCommand> graph;

        void addNewCmd(const pair<string, TMCommand>&);
        void checkIfIsUnique(const TMCommand&) const;
        void appendCmd(const string&, const TMCommand&);
};

#endif // TMCONTROLGRAPH_H
