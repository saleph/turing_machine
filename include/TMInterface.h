#ifndef TMINTERFACE_H
#define TMINTERFACE_H

#include "TMTuringMachine.h"
#include "TMTape.h"

class TMInterface
{
    public:
        // this tape pointer will get ownership of the tape at turingMachine construction
        std::shared_ptr<TMTape> tape;

        TMInterface() : turingMachine(tape) {}; // tape will be 1001 long
        TMInterface(size_t len) : turingMachine(tape, len) {};

        void insertAlphabet(const std::string& alphabet);
        void insertGraph(const std::initializer_list<std::string>& graphAsList);
        void compileInstertedGraph();
        void executeGraphInstantly();
    private:
        TMTuringMachine turingMachine;
        std::vector<std::string> graphAsText;
};

#endif // TMINTERFACE_H
