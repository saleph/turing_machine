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
        const string startPhrase = "Start";
        const string endPhrase = "Stop";
    public:
        shared_ptr<TMTape> tape;
        shared_ptr<TMAlphabet> alphabet;

        TMTuringMachine(size_t length=1001);
        virtual ~TMTuringMachine() {};

        void addToGraph(const string& commandAsText);
        void doStep();
        void backTheGraphToTheBeginning(); // after it the current cmdName is 'Start'
    private:
        unique_ptr<TMControlGraph> graph;
        unique_ptr<TMCommandParser> parser;
        string currentCmdName;

        void doCommandOnTheTape(const TMCommand&);
        void checkIfTheGraphReachedEnd() const throw (EndOfTheControlGraph);
};

#endif // TMTURINGMACHINE_H
