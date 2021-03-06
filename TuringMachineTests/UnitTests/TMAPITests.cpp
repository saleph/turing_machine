#include "TMAPI.h"
#include "TMExceptions.h"
#include <cstdio>

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
#include <boost/filesystem/fstream.hpp>
using namespace std;

struct TMAPITestFixture {
    TMAPITestFixture() : api(tapeLength) {}

    const size_t tapeLength = 11;
    const size_t startHeadPosition = 11/2;
    TMAPI api;
};
BOOST_FIXTURE_TEST_SUITE(plain_API_for_11_long_tape, TMAPITestFixture)

BOOST_AUTO_TEST_CASE( example_proper_use_with_instant_execution ) {
    api.insertAlphabet("#10");
    api.insertGraph({"Start #/1;L next", "next #/1;L next2", "next2 #/0;L Stop"});
    api.compileInsertedGraph();
    api.executeGraphInstantly(); // ########### >> ###011#####
    // head position:                    ^           ^
    std::array<char, 11> outputTape = {'#', '#', '#', '0', '1', '1', '#', '#', '#', '#', '#'};
    BOOST_CHECK_EQUAL_COLLECTIONS(api.tape->begin(), api.tape->end(), outputTape.begin(), outputTape.end());
    BOOST_CHECK_EQUAL(api.tape->getHeadPosition(), startHeadPosition - 3);
}

BOOST_AUTO_TEST_CASE( example_proper_use_with_setting_custom_HeadPositon_with_instant_execution ) {
    api.insertAlphabet("#10");
    api.setHeadPosition(startHeadPosition - 1);
    api.insertGraph({"Start #/1;L next", "next #/1;L next2", "next2 #/0;L Stop"});
    api.compileInsertedGraph();
    api.executeGraphInstantly(); // ########### >> ##011######
    // head position:                   ^           ^
    std::array<char, 11> outputTape = {'#', '#', '0', '1', '1', '#', '#', '#', '#', '#', '#'};
    BOOST_CHECK_EQUAL_COLLECTIONS(api.tape->begin(), api.tape->end(), outputTape.begin(), outputTape.end());
    BOOST_CHECK_EQUAL(api.tape->getHeadPosition(), startHeadPosition - 3 - 1);
}

BOOST_AUTO_TEST_CASE( doSingleStep_on_the_tape ) {
    api.insertAlphabet("#10");
    api.insertGraph({"Start #/1;L next", "next #/1;L next2", "next2 #/0;L Stop"});
    api.compileInsertedGraph();
    api.doSingleStep(); // ########### >> #####1#####
    // head position:           ^             ^
    std::array<char, 11> outputTape = {'#', '#', '#', '#', '#', '1', '#', '#', '#', '#', '#'};
    BOOST_CHECK_EQUAL_COLLECTIONS(api.tape->begin(), api.tape->end(), outputTape.begin(), outputTape.end());
    BOOST_CHECK_EQUAL(api.tape->getHeadPosition(), startHeadPosition - 1);
}

BOOST_AUTO_TEST_CASE( doSingleStep_on_the_tape_with_previously_set_headPosition ) {
    api.insertAlphabet("#10");
    api.setHeadPosition(startHeadPosition - 1);
    api.insertGraph({"Start #/1;L next", "next #/1;L next2", "next2 #/0;L Stop"});
    api.compileInsertedGraph();
    api.doSingleStep(); // ########### >> ####1######
    // head position:          ^             ^
    std::array<char, 11> outputTape = {'#', '#', '#', '#', '1', '#', '#', '#', '#', '#', '#'};
    BOOST_CHECK_EQUAL_COLLECTIONS(api.tape->begin(), api.tape->end(), outputTape.begin(), outputTape.end());
    BOOST_CHECK_EQUAL(api.tape->getHeadPosition(), startHeadPosition - 1 - 1);
}

BOOST_AUTO_TEST_CASE( execution_without_setting_alphabet ) {
    api.insertGraph({"Start #/1;L next", "next #/1;L next2", "next2 #/0;L Stop"});
    api.compileInsertedGraph();
    BOOST_CHECK_THROW(api.doSingleStep(), CharacterOutOfAlphabet);
    BOOST_CHECK_THROW(api.executeGraphInstantly(), CharacterOutOfAlphabet);
    BOOST_CHECK_EQUAL(api.tape->getHeadPosition(), startHeadPosition);
}

BOOST_AUTO_TEST_CASE( execution_without_compilation_of_the_graph ) {
    api.insertAlphabet("#10");
    api.insertGraph({"Start #/1;L next", "next #/1;L next2", "next2 #/0;L Stop"});
    BOOST_CHECK_THROW(api.executeGraphInstantly(), CommandNotExist);
    BOOST_CHECK_THROW(api.doSingleStep(), CommandNotExist);
    BOOST_CHECK_EQUAL(api.tape->getHeadPosition(), startHeadPosition);
}

BOOST_AUTO_TEST_CASE( execution_without_the_graph ) {
    api.insertAlphabet("#10");
    api.compileInsertedGraph();
    BOOST_CHECK_THROW(api.executeGraphInstantly(), CommandNotExist);
    BOOST_CHECK_THROW(api.doSingleStep(), CommandNotExist);
    BOOST_CHECK_EQUAL(api.tape->getHeadPosition(), startHeadPosition);
}

BOOST_AUTO_TEST_SUITE_END()

struct FileProperties {
    FileProperties() : filename(tmpnam(nullptr)) { TMStateWatcher::reset(); }
    unique_ptr<TMFileParser> fileParser; // ptr because it has to be init as the end of ctor
    const string filename;
    const string alphabetAsString = "#01";
    const size_t headPosition = 13;
    const size_t tapeLength = 15;
    const size_t contentPos = 1;
    const string tapeContent = "10";
    const vector<string> graphAsText = {"Start #/1;L next", "next #/1;L next2", "next2 #/0;L Stop"};
};


struct TMAPITestFixtureForLoadingDataFromFile : public FileProperties {
    TMAPITestFixtureForLoadingDataFromFile() : api(11) {
        boost::filesystem::ofstream fileStream (filename);
        fileStream << "// Alphabet\n";
        fileStream << alphabetAsString << '\n';
        fileStream << "// Head position\n";
        fileStream << headPosition << '\n';
        fileStream << "// Tape: [len];[contentPos];[tapeContent]\n";
        fileStream << tapeLength << "; " << contentPos << "; " << tapeContent << '\n';
        fileStream << "// Control graph\n";
        fileStream << graphAsText[0] << '\n';
        fileStream << graphAsText[1] << '\n';
        fileStream << graphAsText[2] << '\n';
        fileStream.close();
    }

    ~TMAPITestFixtureForLoadingDataFromFile() {
        remove(filename.c_str());
    }

    TMAPI api;
};
BOOST_FIXTURE_TEST_SUITE(TMAPI_loading_data_from_file, TMAPITestFixtureForLoadingDataFromFile)

BOOST_AUTO_TEST_CASE( checking_state_of_machine_after_load_and_execution_loaded_graph ) {
    api.getDataFromFile(filename);
    BOOST_CHECK_EQUAL(api.tape->getHeadPosition(), headPosition);
    array<char, 15> tape = {'#', '1', '0', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'};
    BOOST_CHECK_EQUAL_COLLECTIONS(api.tape->begin(), api.tape->end(), tape.begin(), tape.end());
    api.compileInsertedGraph();
    api.executeGraphInstantly();
    array<char, 15> tapeAfterExecution = {'#', '1', '0', '#', '#', '#', '#', '#', '#', '#', '#', '0', '1', '1', '#'};
    BOOST_CHECK_EQUAL_COLLECTIONS(api.tape->begin(), api.tape->end(), tapeAfterExecution.begin(), tapeAfterExecution.end());
    BOOST_CHECK_EQUAL(api.tape->getHeadPosition(), headPosition - 3);
}

BOOST_AUTO_TEST_SUITE_END()
