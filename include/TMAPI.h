#ifndef TMAPI_H
#define TMAPI_H

#include "TMTuringMachine.h"
#include "TMTape.h"
#include "TMFileParser.h"
#include "TMStateWatcher.h"
#include "LazyInitializator.h"

class TMAPI
{
    public:
        // this tape pointer will get ownership of the tape at turingMachine construction
        std::shared_ptr<TMTape> tape;
        TMAPI(const size_t len=1001) : turingMachine(tape, len) {}

        void insertAlphabet(const std::string& alphabet);
        void setHeadPosition(const size_t& pos);
        void insertGraph(const std::initializer_list<std::string>& graphAsList);
        void insertGraph(const std::vector<std::string>& graphAsVector);
        void compileInsertedGraph();
        void doSingleStep();
        void executeGraphInstantly();
        void turnBackGraphToStartPosition();

        void getDataFromFile(const std::string& filename);
    private:
        TMTuringMachine turingMachine;
        std::unique_ptr<TMFileParser> fileParser;
        std::vector<std::string> graphAsText;

        void initializeFileParser(const std::string& filename);
        void checkIfDataWasInserted() const throw (DataFromFileDoesntInserted);
        void getDataFromStateWatcher();
        void setAlphabetWithValueFromStateWatcher();
        void setHeadPositionWithValueFromStateWatcher();
        void setTapeLengthWithValueFromStateWatcher();
        void setTapeContentWithValueFromStateWatcher();
        void setGraphAsTextWithValueFromStateWatcher();
};

#endif // TMAPI_H
