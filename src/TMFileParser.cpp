#include "TMFileParser.h"

void TMFileParser::parseToStateWatcher() {
    parseAlphabet();
    parseHeadPosition();
    parseTapeInfo();
    parseControlGraph();
}

void TMFileParser::parseAlphabet() {
    getLine();
    if (isCurrentLineAComment())
        getLine(); // simply if the line is a comment - skip it
    checkIfLineIsAlphabet();
    putAlphabetIntoStateWatcher();
}

std::istream& TMFileParser::getLine() {
    return std::getline(fileStream, currentLine);
}

bool TMFileParser::isCurrentLineAComment() const {
    return std::regex_match(currentLine, commentPattern);
}

void TMFileParser::checkIfLineIsAlphabet() throw (TMInvalidAlphabetSyntax) {
    if (!std::regex_match(currentLine, regexTokens, alphabetPattern))
        throw TMInvalidAlphabetSyntax();
}

void TMFileParser::putAlphabetIntoStateWatcher() {
    *TMStateWatcher::alphabetAsString = regexTokens[1];
}

void TMFileParser::parseHeadPosition() {
    getLine();
    if (isCurrentLineAComment())
        getLine(); // simply if the line is a comment - skip it
    checkIfLineIsHeadPosition();
    putHeadPositionIntoStateWatcher();
}

void TMFileParser::checkIfLineIsHeadPosition() throw (TMInvalidHeadPositionSyntax) {
    if (!std::regex_match(currentLine, regexTokens, headPositionPattern))
        throw TMInvalidHeadPositionSyntax();
}

void TMFileParser::putHeadPositionIntoStateWatcher() {
    const size_t headPosition = getSize_tNumberFrom(regexTokens[1]);
    *TMStateWatcher::headPosition = headPosition;
}

size_t TMFileParser::getSize_tNumberFrom(const std::string& str) {
    return static_cast<size_t>(std::stoull(str));
}

void TMFileParser::parseTapeInfo() {
    getLine();
    if (isCurrentLineAComment())
        getLine(); // simply if the line is a comment - skip it
    checkIfLineIsTapeInfo();
    putTapeInfoIntoStateWatcher();
}

void TMFileParser::checkIfLineIsTapeInfo() throw (TMInvalidTapeContentSyntax) {
    if (!std::regex_match(currentLine, regexTokens, tapeContentPattern))
        throw TMInvalidTapeContentSyntax();
}

void TMFileParser::putTapeInfoIntoStateWatcher() {
    const size_t tapeLength = getSize_tNumberFrom(regexTokens[1]);
    *TMStateWatcher::tapeLength = tapeLength;
    const size_t tapeContentPosition = getSize_tNumberFrom(regexTokens[2]);
    *TMStateWatcher::tapeContentPosition = tapeContentPosition;
    *TMStateWatcher::tapeContent = regexTokens[3];
}

void TMFileParser::parseControlGraph() {
    while (getLine()) {
        if (isCurrentLineAComment())
            getLine();
        checkIfLineIsCommand();
        putCommandIntoGraphAsText();
    }
    putGraphAsTextIntoStateWatcher();
}

void TMFileParser::checkIfLineIsCommand() throw (TMInvalidControlGraphSyntax) {
    if (!std::regex_match(currentLine, regexTokens, graphPattern))
        throw TMInvalidControlGraphSyntax();
}

void TMFileParser::putCommandIntoGraphAsText() {
    graphAsText.push_back(regexTokens[1]);
}

void TMFileParser::putGraphAsTextIntoStateWatcher() {
    *TMStateWatcher::graphAsText = graphAsText;
}
