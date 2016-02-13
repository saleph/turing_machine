#include "TMFileParser.h"

void TMFileParser::parseToStateWatcher() {
/*
    parseAlphabet();
    parseHeadPosition();
    parseTapeInfo();
    parseControlGraph();*/
}
/*
void TMFileParser::parseAlphabet() {
    getLine();
    if (isCurrentLineAComment())
        getLine(); // simply if the line is a comment - skip it
    checkIfLineIsAlphabet();
    putAlphabetIntoStateWatcher();
}

std::ifstream& TMFileParser::getLine() {
    return std::getline(fileStream, currentLine);
}

bool TMFileParser::isCurrentLineAComment() const {
    return std::regex_match(currentLine, commentPattern);
}

void TMFileParser::checkIfLineIsAlphabet() {
    if (!std::regex_match(currentLine, regexTokens, alphabetPattern))
        throw
}*/
