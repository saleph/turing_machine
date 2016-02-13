#ifndef TMFILEPARSER_H
#define TMFILEPARSER_H

#include "TMStateWatcher.h"
#include <fstream>
#include <regex>


class TMFileParser
{
    const std::regex commentPattern = std::regex (
    "[\\/]{2}" // 2 slashes at the start of comment
    ".*"       // content of the comment
    );
    const std::regex alphabetPattern = std::regex (
    "^"        // start of line
    "("        // start of matched group
    "[\\/]?"   // first, optional slash as first char of alphabet
    "[^\\/]"   // but if occurs second slash - DON'T match regexp
    ".+"       // the rest of alphabet
    ")"        // the end of matched group
    );
    const std::regex headPositionPattern = std::regex (
    "^"        // start of line
    "("        // start of matched group
    "[^\\/]"   // but if occurs slash - DON'T match regexp
    "[0-9]+"   // head position as number
    ")"        // the end of matched group
    );
    const std::regex tapeContentPattern = std::regex (
    "^"        // start of line
    "([0-9]+)" // tape length
    "; "       // semicolon separating position and length
    "([0-9]+)" // where tape content should begin
    "; "       // semicolon separating position and the content
    "(.*)"     // the content of the tape
    );
    const std::regex graphPattern = std::regex (
    "^"        // start of line
    "("        // start of matched group
    "[\\/]?"   // first, optional slash, the at the start of command name
    "[^\\/]"   // but if occurs second slash - DON'T match regexp
    ".+"       // rest of the command's body
    ")"        // the end of matched group
    );
    public:
        TMFileParser(const std::string& fileName) : fileStream(fileName) {};

        void parseToStateWatcher();
    private:
        std::ifstream fileStream;
        std::smatch regexTokens;
        std::string currentLine;

        void parseAlphabet();

        std::ifstream& getLine();
};

#endif // TMFILEPARSER_H
