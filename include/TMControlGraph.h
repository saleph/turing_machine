#ifndef TMCONTROLGRAPH_H
#define TMCONTROLGRAPH_H

#include "TMCommand.h"
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;


class TMControlGraph
{
    public:
        TMControlGraph();
        virtual ~TMControlGraph();

        TMCommand& operator[] (const string val) { return graph[val]; }
    protected:
    private:
        unordered_map<string, TMCommand> graph;
};

#endif // TMCONTROLGRAPH_H
