#include <iostream>
#include "TMTape.h"
#include "TMAlphabet.h"
#include "TMInterface.h"
using namespace std;

int main() {
    TMInterface interface(11);
    interface.turingMachine.alphabet->setAlphabet("#10");
    interface.insertGraph({"Start #/1;L next", "next #/1;L next2", "next2 #/0;L Stop"});
    interface.compileInstertedGraph();
    interface.turingMachine.instantExecution();
    for (auto sign : *interface.turingMachine.tape) cout<<sign;
    return 0;
}
