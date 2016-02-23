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
        std::shared_ptr<TMAlphabet> alphabet;
        std::unique_ptr<TMControlGraph> graph;

        TMTuringMachine(size_t length=1001);
        // this ctor shares ownership of the tape with tapePtr given by reference
        TMTuringMachine(std::shared_ptr<TMTape>& tapePtr, size_t length=1001)
                : TMTuringMachine(length) { tapePtr = tape; }

        std::shared_ptr<TMTape> getOwnershipOfTheTape() { return tape; }
        void addToGraph(const std::string& commandAsText, const int& location=-1);
        void doStep();
        void executeGraphInstantly();
        void backTheGraphToTheBeginning(); // after it the current cmdName is 'Start'
        int getLocationOfLastCommand() const;
    private:
        std::shared_ptr<TMTape> tape;
        std::unique_ptr<TMCommandParser> parser;
        std::string currentCmdName;
        int currentCmdLocation;

        void doCommandOnTheTape(const TMCommand&);
        void checkIfTheGraphReachedEnd() const throw (EndOfTheControlGraph);
};

#endif // TMTURINGMACHINE_H
