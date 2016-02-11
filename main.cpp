#include <iostream>
#include "TMTape.h"
#include "TMAlphabet.h"
#include "TMInterface.h"
using namespace std;

int main() {
    TMInterface interface(11);
    interface.turingMachine.alphabet->setAlphabet("#10");
    interface.turingMachine.addToGraph("Start #/1;L next");
    interface.turingMachine.addToGraph("next #/1;L next2");
    interface.turingMachine.addToGraph("next2 #/0;L Stop");
    interface.turingMachine.instantExecution();
    for (auto sign : *interface.turingMachine.tape) cout<<sign;
    return 0;
}
