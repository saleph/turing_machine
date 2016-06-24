#include <iostream>
#include <cstring>
#include "TMAPI.h"
using namespace std;

void showHelp();

/*
 * Todo:
 * - dumping into file
 * - shorten tape decryptor
 * - in TMTuringMachine - ability to use and compare two tapes (for unit testing purposes)
 * - new class - StateDumper, which will use TuringMachine method to transfer its state into TMStateWatcher
 * and then dump all data into a file
 * - UNIT TESTING - method of TMAPI gets 2 shorten tapes as strings, builds 2 tapes from it and do the comparison;
 * should return a pair of vector of booleans (passed/not) and vector of EXCEPTIONS - for futer use in e.what()
 */

int main(int argc, char* argv[]) {
    if (argc <= 1)
        throw std::invalid_argument("Filepath not entered! Try again.");
    if (!std::strcmp(argv[1], "help")) {
        showHelp();
        cout << "Run simulator once again with path to file!\n";
        abort();
    }
    TMAPI api(11);
    api.getDataFromFile(argv[1]);
    api.compileInsertedGraph();
    cout << "Before execution:\n";
    for (auto sign : *api.tape) cout << sign;
    cout << "; " << api.tape->getHeadPosition() << '\n';
    for (size_t i = 0; i < api.tape->getHeadPosition(); i++) cout<<' ';
    cout << "^\n" << endl;

    api.executeGraphInstantly();

    cout << "After execution:\n";
    for (auto sign : *api.tape) cout<<sign;
    cout << "; " << api.tape->getHeadPosition() << '\n';
    for (size_t i = 0; i < api.tape->getHeadPosition(); i++) cout<<' ';
    cout << "^" << endl;

    return 0;
}


void showHelp() {
    cout << "Example use: $ ./tm fileWithGraph.txt\n";
    cout << "Example file:\n";
    cout << "// Alphabet\n";
    cout << "#01\n";
    cout << "// Head position on tape\n";
    cout << "4\n";
    cout << "// [tapeLength]; [contentPosition]; [tapeContent]\n";
    cout << "16; 8; 111111\n";
    cout << "// CONTROL GRAPH:\n";
    cout << "Start #/0;L next\n";
    cout << "next #/1;L next2\n";
    cout << "next2 #/0;L Stop\n";
}
