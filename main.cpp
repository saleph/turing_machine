#include <iostream>
#include "TMTape.h"
#include "TMAlphabet.h"
using namespace std;

int main() {
    auto alpha = (make_shared<TMAlphabet>("#1"));
    TMTape tmTapeInstance(5, alpha);
    tmTapeInstance[1] = '1';
    for (auto el : tmTapeInstance)
        cout << el;
    return 0;
}
