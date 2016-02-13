#include <iostream>
#include "TMTape.h"
#include "TMAlphabet.h"
#include "TMAPI.h"
using namespace std;

int main() {
    TMAPI api(11);
    api.insertAlphabet("#10");
    api.insertGraph({"Start #/1;L next", "next #/1;L next2", "next2 #/0;L Stop"});
    api.compileInsertedGraph();
    api.executeGraphInstantly();
    for (auto sign : *api.tape) cout<<sign;
    return 0;
}
