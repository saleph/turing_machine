#ifndef TMTURINGMACHINE_H
#define TMTURINGMACHINE_H

#include "TMTape.h"
#include "TMAlphabet.h"
#include "TMCommandParser.h"
#include "TMControlGraph.h"
#include <memory>
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_unique;
using std::string;

class TMTuringMachine
{
    public:
        TMTuringMachine(unsigned int length);
        virtual ~TMTuringMachine() {};

        void addToGraph(const string& commandAsText);
        void doStep();
    private:
        unique_ptr<TMControlGraph> graph;
        unique_ptr<TMCommandParser> parser;
        shared_ptr<TMTape> tape;
        shared_ptr<TMAlphabet> alphabet;
        string currentCmdName;

        void doCommandOnTheTape(const TMCommand&);
};

#endif // TMTURINGMACHINE_H
