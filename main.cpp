#include <iostream>
#include "TMTape.h"
#include "TMAlphabet.h"
#include "TMInterface.h"
using namespace std;

int main() {
    TMInterface interface(11);
    interface.insertAlphabet("#10");
    interface.insertGraph({"Start #/1;L next", "next #/1;L next2", "next2 #/0;L Stop"});
    interface.compileInstertedGraph();
    interface.executeGraphInstantly();
    for (auto sign : *interface.tape) cout<<sign;
    return 0;
}
