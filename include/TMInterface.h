#ifndef TMINTERFACE_H
#define TMINTERFACE_H

#include "TMTuringMachine.h"
#include "TMTape.h"

class TMInterface
{
    public:
        // turingMachine offers direct manipulation on its tape by (*turingMachine.tape)[]
        // with alphabet - it is possible to simlply set new one: turingMachine.alphabet->setAlphabet()
        TMTuringMachine turingMachine;
        TMInterface() : turingMachine() {}; // tape will be 1001 long
        TMInterface(size_t len) : turingMachine(len) {};

        void insertGraph(const std::initializer_list<std::string>& graphAsList);
        void compileInstertedGraph();
    private:
        std::vector<std::string> graphAsText;
};

#endif // TMINTERFACE_H
