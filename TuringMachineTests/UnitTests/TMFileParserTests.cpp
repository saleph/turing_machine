#include "TMFileParser.h"
#include "TMStateWatcher.h"
#include "TMExceptions.h"
#include <memory>
#include <cstdio>
#include <fstream>

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
#include <boost/filesystem/fstream.hpp>
using namespace std;

BOOST_AUTO_TEST_SUITE(TMFileParser_test_suite)

struct TMFileParserTestFixtureProperties {
    TMFileParserTestFixtureProperties() : filename(tmpnam(nullptr)) {}
    unique_ptr<TMFileParser> fileParser; // ptr because it has to be init as the end of ctor
    const string filename;
    const string alphabetAsString = "#01";
    const size_t headPosition = 5;
    const size_t tapeLength = 11;
    const size_t contentPos = 2;
    const string tapeContent = "101#00";
    const vector<string> graphAsText = {"Start #/1;L next", "next #/1;L next2", "next2 #/0;L Stop"};
};


// =========== PROPER FILE WITH COMMENTS ===========
struct TMFileParserTestFixtureForProperFileWithComments : public TMFileParserTestFixtureProperties {
    TMFileParserTestFixtureForProperFileWithComments() {
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
        fileParser = make_unique<TMFileParser>(filename);
    }

    ~TMFileParserTestFixtureForProperFileWithComments() {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(for_file_with_comments, TMFileParserTestFixtureForProperFileWithComments) {
    fileParser->parseToStateWatcher();
    BOOST_REQUIRE(TMStateWatcher::prepared());
    BOOST_CHECK_EQUAL(*TMStateWatcher::alphabetAsString, alphabetAsString);
    BOOST_CHECK_EQUAL(*TMStateWatcher::headPosition, headPosition);
    BOOST_CHECK_EQUAL(*TMStateWatcher::tapeLength, tapeLength);
    BOOST_CHECK_EQUAL(*TMStateWatcher::tapeContentPosition, contentPos);
    BOOST_CHECK_EQUAL(*TMStateWatcher::tapeContent, tapeContent);
    BOOST_CHECK_EQUAL_COLLECTIONS(TMStateWatcher::graphAsText->begin(), TMStateWatcher::graphAsText->end(),
                                  graphAsText.begin(), graphAsText.end());
}

// =========== PROPER FILE WITHOUT COMMENTS ===========
struct TMFileParserTestFixtureForProperFileWithoutComments : public TMFileParserTestFixtureProperties {
    TMFileParserTestFixtureForProperFileWithoutComments() {
        boost::filesystem::ofstream fileStream (filename);
        fileStream << alphabetAsString << '\n';
        fileStream << headPosition << '\n';
        fileStream << tapeLength << "; " << contentPos << "; " << tapeContent << '\n';
        fileStream << graphAsText[0] << '\n';
        fileStream << graphAsText[1] << '\n';
        fileStream << graphAsText[2] << '\n';
        fileStream.close();
        fileParser = make_unique<TMFileParser>(filename);
    }

    ~TMFileParserTestFixtureForProperFileWithoutComments() {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(for_file_without_comments, TMFileParserTestFixtureForProperFileWithoutComments) {
    fileParser->parseToStateWatcher();
    BOOST_REQUIRE(TMStateWatcher::prepared());
    BOOST_CHECK_EQUAL(*TMStateWatcher::alphabetAsString, alphabetAsString);
    BOOST_CHECK_EQUAL(*TMStateWatcher::headPosition, headPosition);
    BOOST_CHECK_EQUAL(*TMStateWatcher::tapeLength, tapeLength);
    BOOST_CHECK_EQUAL(*TMStateWatcher::tapeContentPosition, contentPos);
    BOOST_CHECK_EQUAL(*TMStateWatcher::tapeContent, tapeContent);
    BOOST_CHECK_EQUAL_COLLECTIONS(TMStateWatcher::graphAsText->begin(), TMStateWatcher::graphAsText->end(),
                                  graphAsText.begin(), graphAsText.end());
}


// =========== FILE WITHOUT ALPHABET (will be commented) ===========
struct TMFileParserTestFixtureForFileWithoutAlphabet : public TMFileParserTestFixtureProperties {
    TMFileParserTestFixtureForFileWithoutAlphabet() {
        boost::filesystem::ofstream fileStream (filename);
        fileStream << "// " << alphabetAsString << '\n';
        fileStream << headPosition << '\n';
        fileStream << tapeLength << "; " << contentPos << "; " << tapeContent << '\n';
        fileStream << graphAsText[0] << '\n';
        fileStream << graphAsText[1] << '\n';
        fileStream << graphAsText[2] << '\n';
        fileStream.close();
        fileParser = make_unique<TMFileParser>(filename);
    }

    ~TMFileParserTestFixtureForFileWithoutAlphabet() {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(for_file_without_alphabet, TMFileParserTestFixtureForFileWithoutAlphabet) {
    BOOST_CHECK_THROW(fileParser->parseToStateWatcher(), TMInvalidAlphabetSyntax);
    BOOST_CHECK(!TMStateWatcher::prepared());
}


// =========== FILE WITHOUT HEAD POSITION (will be commented) ===========
struct TMFileParserTestFixtureForFileWithoutHeadPosition : public TMFileParserTestFixtureProperties {
    TMFileParserTestFixtureForFileWithoutHeadPosition() {
        boost::filesystem::ofstream fileStream (filename);
        fileStream << alphabetAsString << '\n';
        fileStream << "// " << headPosition << '\n';
        fileStream << tapeLength << "; " << contentPos << "; " << tapeContent << '\n';
        fileStream << graphAsText[0] << '\n';
        fileStream << graphAsText[1] << '\n';
        fileStream << graphAsText[2] << '\n';
        fileStream.close();
        fileParser = make_unique<TMFileParser>(filename);
    }

    ~TMFileParserTestFixtureForFileWithoutHeadPosition() {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(for_file_without_HeadPosition, TMFileParserTestFixtureForFileWithoutHeadPosition) {
    BOOST_CHECK_THROW(fileParser->parseToStateWatcher(), TMInvalidHeadPositionSyntax);
    BOOST_CHECK(!TMStateWatcher::prepared());
}


// =========== FILE WITHOUT TAPE CONTENT (will be commented) ===========
struct TMFileParserTestFixtureForFileWithoutTapeContent : public TMFileParserTestFixtureProperties {
    TMFileParserTestFixtureForFileWithoutTapeContent() {
        boost::filesystem::ofstream fileStream (filename);
        fileStream << alphabetAsString << '\n';
        fileStream <<  headPosition << '\n';
        fileStream << "// " << tapeLength << "; " << contentPos << "; " << tapeContent << '\n';
        fileStream << graphAsText[0] << '\n';
        fileStream << graphAsText[1] << '\n';
        fileStream << graphAsText[2] << '\n';
        fileStream.close();
        fileParser = make_unique<TMFileParser>(filename);
    }

    ~TMFileParserTestFixtureForFileWithoutTapeContent() {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(for_file_without_TapeContent, TMFileParserTestFixtureForFileWithoutTapeContent) {
    BOOST_CHECK_THROW(fileParser->parseToStateWatcher(), TMInvalidTapeContentSyntax);
    BOOST_CHECK(!TMStateWatcher::prepared());
}


// =========== FILE WITHOUT CONTROL GRAPH (will be commented) ===========
struct TMFileParserTestFixtureForFileWithoutControlGraph : public TMFileParserTestFixtureProperties {
    TMFileParserTestFixtureForFileWithoutControlGraph() {
        boost::filesystem::ofstream fileStream (filename);
        fileStream << alphabetAsString << '\n';
        fileStream <<  headPosition << '\n';
        fileStream << tapeLength << "; " << contentPos << "; " << tapeContent << '\n';
        fileStream << "// " << graphAsText[0] << '\n';
        fileStream << "// " << graphAsText[1] << '\n';
        fileStream << "// " << graphAsText[2] << '\n';
        fileStream.close();
        fileParser = make_unique<TMFileParser>(filename);
    }

    ~TMFileParserTestFixtureForFileWithoutControlGraph() {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(for_file_without_ControlGraph, TMFileParserTestFixtureForFileWithoutControlGraph) {
    BOOST_CHECK_THROW(fileParser->parseToStateWatcher(), TMInvalidControlGraphSyntax);
    BOOST_CHECK(!TMStateWatcher::prepared());
}

BOOST_AUTO_TEST_SUITE_END()
