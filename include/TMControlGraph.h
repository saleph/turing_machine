#ifndef TMCONTROLGRAPH_H
#define TMCONTROLGRAPH_H

#include "TMCommand.h"
#include "TMStringCharPair.h"
#include "TMExceptions.h"
#include <unordered_map>
#include <string>


class TMControlGraph
{
    public:
        TMControlGraph() {}

        const TMCommand& operator[] (const TMStringCharPair&) const throw (CommandNotExist);
        void operator+= (const std::pair<std::string, TMCommand>& cmd) throw (CommandAlreadyExist);
        std::string getCommandNameWith(int location) const;
        void clear();
    private:
        std::unordered_map<TMStringCharPair, TMCommand> graph;

        void addNewCmd(const std::pair<std::string, TMCommand>&) throw (CommandAlreadyExist);
        void checkIfIsUnique(const TMStringCharPair&) throw (CommandAlreadyExist);
        void appendCmd(TMStringCharPair&, TMCommand&);
};

#endif // TMCONTROLGRAPH_H
