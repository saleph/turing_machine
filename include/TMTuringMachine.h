#ifndef TMTURINGMACHINE_H
#define TMTURINGMACHINE_H

#include "TMTape.h"
#include "TMAlphabet.h"
#include "TMCommandParser.h"
#include "TMControlGraph.h"
#include <memory>

class TMTuringMachine
{
        const std::string startPhrase = "Start";
        const std::string endPhrase = "Stop";
    public:
        std::shared_ptr<TMTape> tape;
        std::shared_ptr<TMAlphabet> alphabet;

        TMTuringMachine(size_t length=1001);
        virtual ~TMTuringMachine() {};

        std::shared_ptr<TMTape> getOwnershipOfTheTape() { return tape; };
        void addToGraph(const std::string& commandAsText);
        void doStep();
        void instantExecution();
        void backTheGraphToTheBeginning(); // after it the current cmdName is 'Start'
    private:
        std::unique_ptr<TMControlGraph> graph;
        std::unique_ptr<TMCommandParser> parser;
        std::string currentCmdName;

        void doCommandOnTheTape(const TMCommand&);
        void checkIfTheGraphReachedEnd() const throw (EndOfTheControlGraph);
};

#endif // TMTURINGMACHINE_H
