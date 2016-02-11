#ifndef TMAPI_H
#define TMAPI_H

#include "TMTuringMachine.h"
#include "TMTape.h"

class TMAPI
{
    public:
        // this tape pointer will get ownership of the tape at turingMachine construction
        std::shared_ptr<TMTape> tape;
        TMAPI(size_t len=1001) : turingMachine(tape, len) {};

        void insertAlphabet(const std::string& alphabet);
        void setHeadPosition(const size_t pos);
        void insertGraph(const std::initializer_list<std::string>& graphAsList);
        void compileInstertedGraph();
        void doSingleStep();
        void executeGraphInstantly();
        void turnBackGraphToStartPosition();
    private:
        TMTuringMachine turingMachine;
        std::vector<std::string> graphAsText;
};

#endif // TMAPI_H
